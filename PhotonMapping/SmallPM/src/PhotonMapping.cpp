/*********************************************************************************
Copyright (C) 2014 Adrian Jarabo (ajarabo@unizar.es)
Copyright (C) 2014 Diego Gutierrez (diegog@unizar.es)
All rights reserved.

This is an educational Ray Tracer developed for the course 'Informatica Grafica'
(Computer Graphics) tought at Universidad de Zaragoza (Spain). As such, it does not 
intend to be fast or general, but just to provide an educational tool for undergraduate
students. 

This software is provided as is, and any express or implied warranties are disclaimed.
In no event shall copyright holders be liable for any damage.
**********************************************************************************/
#define _USE_MATH_DEFINES

#include "PhotonMapping.h"
#include "World.h"
#include "Intersection.h"
#include "Ray.h"
#include "BSDF.h"
#include <random>
#include <cmath>

//*********************************************************************
// Compute the photons by tracing the Ray 'r' from the light source
// through the scene, and by storing the intersections with matter
// in the lists 'xx_photons', storing the diffuse (global) and caustic
// photons respectively. For efficiency, both are computed at the same
// time, since computing them separately would result into a lost of
// several samples marked as caustic or diffuse.
// Same goes with the boolean 'direct', that specifies if direct 
// photons (from light to surface) are being stored or not. 
// The initial traced photon has energy defined by the tristimulus
// 'p', that accounts for the emitted power of the light source.
// The function will return true when there are more photons (caustic
// or diffuse) to be shot, and false otherwise.
//---------------------------------------------------------------------
bool PhotonMapping::trace_ray(const Ray& r, const Vector3 &p, 
			   std::list<Photon> &global_photons, std::list<Photon> &caustic_photons, bool direct, bool direct_only)
{
#ifndef MAX_PHOTON_ITERATIONS
#define MAX_PHOTON_ITERATIONS 20
#endif



	//Check if max number of shots done...
	if( ++m_nb_current_shots > m_max_nb_shots )
	{
		return false;
	}
	
	// Compute irradiance photon's energy
	Vector3 energy(p);
	
	Ray photon_ray(r);
	photon_ray.shift();

	bool is_caustic_particle = false;

	//Iterate the path
	while(1)
	{
		// Throw ray and update current_it
		Intersection it;
		world->first_intersection(photon_ray, it);

		if( !it.did_hit() )
			break;

		//Check if has hit a delta material...
		if( it.intersected()->material()->is_delta() )
		{
			// If delta material, then is caustic...
			// Don't store the photon!
			is_caustic_particle = true;
		}
		else if (photon_ray.get_level() > 0 || direct || direct_only )
		{
			//If non-delta material, store the photon!
			if( is_caustic_particle )	
			{				
				//If caustic particle, store in caustics
				if( caustic_photons.size() < m_nb_caustic_photons )
					caustic_photons.push_back( Photon(it.get_position(), photon_ray.get_direction(), energy ));
			}
			else						
			{
				//If non-caustic particle, store in global
				if( global_photons.size() < m_nb_global_photons )
					global_photons.push_back( Photon(it.get_position(), photon_ray.get_direction(), energy ));
			}
			is_caustic_particle = false;
		}	
		
		Real pdf;

		Vector3 surf_albedo = it.intersected()->material()->get_albedo(it);
		Real avg_surf_albedo = surf_albedo.avg();

		Real epsilon2 = static_cast<Real>(rand())/static_cast<Real>(RAND_MAX);
		while (epsilon2 < 0.)
			epsilon2 = static_cast<Real>(rand())/static_cast<Real>(RAND_MAX);
		
		if (epsilon2 > avg_surf_albedo || photon_ray.get_level() > MAX_PHOTON_ITERATIONS ) 
			break;
		
		if (direct_only && !is_caustic_particle && photon_ray.get_level() > 1)
			break;

		// Random walk's next step
		// Get sampled direction plus pdf, and update attenuation
		it.intersected()->material()->get_outgoing_sample_ray(it, photon_ray, pdf );

		// Shade...
		energy = energy*surf_albedo;
		if( !it.intersected()->material()->is_delta() )
			energy *= dot_abs(it.get_normal(), photon_ray.get_direction())/M_PI;		

		energy = energy /(pdf*avg_surf_albedo);
	}
	
	if( caustic_photons.size() == m_nb_caustic_photons && 
		global_photons.size() == m_nb_global_photons )
	{
		m_max_nb_shots = m_nb_current_shots-1;
		return false;
	}

	return true;
}

//*********************************************************************
//                        Preprocess step of photon mapping,
// where the photons are traced through the scene. To do it,
// these steps are followed for each shoot:
//  1 - Sample a world's light source in the scene to create
//		the initial direct photon from the light source.
//	2 - Trace the photon through the scene storing the inter-
//		sections between the photons and matter. You can use
//		the function 'trace_ray' for this purpose.
//	3 - Finally, once all the photons have been shot, you'll
//		need to build the photon maps, that will be used later
//		for rendering.
//---------------------------------------------------------------------

void PhotonMapping::preprocess()
{
	static std::random_device rd;
	static std::mt19937 random(rd());
	std::uniform_real_distribution<Real> rs_dist(-1.0, 1.0);
	std::uniform_int_distribution<int> ls_dist(0, world->nb_lights()-1);
	bool more_shots = true;
	Real x, y, z;
	std::list<Photon> global_photons;
	std::list<Photon> caustics_photons;

	while (more_shots) {
		// Rejection Sampling
		do {
			x = rs_dist(random);
			y = rs_dist(random);
			z = rs_dist(random);
		} while (x * x + y * y + z * z > 1);
		
		// Get a random light source (Monte Carlo)
		LightSource* light = world->light_source_list[ls_dist(random)];

		Ray light_ray(light->get_position(), Vector3(x, y, z).normalize());

		// Trace ray from light, bouncing and getting a list of photos (one per bounce/intersection) to store.
		more_shots = trace_ray(light_ray, light->get_intensities(), global_photons, caustics_photons, false, false);
	}

	// Store photons from global ilumination on KDTree
	if (!global_photons.empty()) {
		for (Photon photon : global_photons) {
			std::vector<Real> pos = { photon.position[0], photon.position[1], photon.position[2] };
			photon.flux = photon.flux / 
				((global_photons.size() + caustics_photons.size()) / world->nb_lights()) // Scale photon with light intensity for number of light shoots.
				* (4 * M_PI) // Sampled solid angle (Full sphere)
				* (1 / (Real) world->nb_lights()); // Monte Carlo: probability to shoot from this light (in this case, all lights have the same %).
			m_global_map.store(pos, photon);
		}
		m_global_map.balance();
	}

	// Store photons from global ilumination on KDTree
	if (!caustics_photons.empty()) {
		for (Photon photon : caustics_photons) {
			std::vector<Real> pos = { photon.position[0], photon.position[1], photon.position[2] };
			photon.flux = photon.flux /
				((global_photons.size() + caustics_photons.size()) / world->nb_lights()) // Scale photon with light intensity for number of light shoots.
				* (4 * M_PI) // Sampled solid angle (Full sphere)
				* (1 / (Real)world->nb_lights()); // Monte Carlo: probability to shoot from this light (in this case, all lights have the same %).
			m_caustics_map.store(pos, photon);
		}
		m_caustics_map.balance();
	}
	
}

//*********************************************************************
//                   Function that computes the rendering equation 
// using radiance estimation with photon mapping, using the photon
// maps computed as a proprocess. Note that in this fuction is handled
// both direct and global illumination, together with recursive the 
// recursive evaluation of delta materials.
// In principle, the class is prepared to perform radiance estimation
// using k-nearest neighbors ('m_nb_photons') to define the bandwidth
// of the kernel.
//---------------------------------------------------------------------
Vector3 PhotonMapping::shade(Intersection &it0)const
{
	unsigned int mode = 0;

	Real near_photons;
	bool delta_bouncing, raytraced_emitted_light, indirect_light, fix_photons, BRDF_at_indirect;
	switch (mode) {
	case 0: // Debug and testing. DIY.
		delta_bouncing = false;
		raytraced_emitted_light = false;
		indirect_light = true;
		fix_photons = false;
		BRDF_at_indirect = false;
		near_photons = 1;
		break;
	case 1: // Photon map
		delta_bouncing = false;
		raytraced_emitted_light = false;
		indirect_light = true;
		fix_photons = false;
		BRDF_at_indirect = false;
		near_photons = 1;
		break;
	case 2: // Photon map ilumination only
		delta_bouncing = true;
		raytraced_emitted_light = false;
		indirect_light = true;
		fix_photons = true;
		BRDF_at_indirect = true;
		near_photons = m_nb_photons;
		break;
	case 3: // Raytraced emitted (direct) light only
		delta_bouncing = true;
		raytraced_emitted_light = true;
		indirect_light = false;
		fix_photons = false;
		BRDF_at_indirect = false;
		near_photons = m_nb_photons;
		break;
	default: // Raytraced emitted (direct) light and Photon map ilumination
		delta_bouncing = true;
		raytraced_emitted_light = true;
		indirect_light = true;
		fix_photons = true;
		BRDF_at_indirect = true;
		near_photons = m_nb_photons;
		break;
	}

	Vector3 directL(0), globalL(0), causticsL(0);
	Vector3 W(1);
	Intersection it(it0);
	std::vector<const KDTree<Photon, 3U>::Node*> global_photons, global_photons_fix, caustics_photons, caustics_photons_fix;
	Real radius, area;

	// Delta bouncing
	if (delta_bouncing) {
		int nb_bounces = 0;
		while (it.did_hit() && it.intersected()->material()->is_delta() && ++nb_bounces < MAX_NB_BOUNCES) {
			Ray r; Real pdf;
			it.intersected()->material()->get_outgoing_sample_ray(it, r, pdf); // Get outgoing ray (r) and probability distribution function (pdf)
			W = W * it.intersected()->material()->get_albedo(it) / pdf; // Weight of each delta bounce

			r.shift();
			world->first_intersection(r, it);
		}
	}

	// Shading at non delta material, after (or not) bouncing on delta materials.
	if (it.did_hit() && !it.intersected()->material()->is_delta()) {
		vector<Real> pos = { it.get_position()[0], it.get_position()[1], it.get_position()[2] };

		// Direct light
		if (raytraced_emitted_light) {
			for (LightSource* light : world->light_source_list) {
				Vector3 incoming_light = light->get_incoming_light(it.get_position()); // Intensity of light coming
				Vector3 incoming_light_dir = light->get_incoming_direction(it.get_position()); // Direction from where light is coming
				if (light->is_visible(it.get_position())) {
					directL += incoming_light * (it.intersected()->material()->get_albedo(it) / M_PI) * dot_abs(it.get_normal(), incoming_light_dir);
				}
			}
			directL / world->nb_lights();
		}
		
		// Indirect light
		if (indirect_light) {

			// Global
			m_global_map.find(pos, near_photons, global_photons, radius);

			if (!global_photons.empty()) {

				// Reject photons from near geometry. Rejection based on incoming direction of photon.
				if (fix_photons) { 
					fix_near_photons(global_photons, it, global_photons_fix, radius);
				}
				else {
					global_photons_fix = global_photons;
				}

				// Apply kernel for radiance estimation at this point with the selected photons.
				globalL = cone_kernel(global_photons_fix, it, radius, 2.0f, BRDF_at_indirect);
			}

			// Caustics
			m_caustics_map.find(pos, near_photons, caustics_photons, radius);

			if (!caustics_photons.empty()) {

				// Reject photons from near geometry. Rejection based on incoming direction of photon.
				if (fix_photons) {
					fix_near_photons(caustics_photons, it, global_photons_fix, radius);
				}
				else {
					caustics_photons_fix = caustics_photons;
				}

				// Apply kernel for radiance estimation at this point with the selected photons.
				causticsL = cone_kernel(caustics_photons_fix, it, radius, 2.0f, BRDF_at_indirect);

			}
		}
		// End of Indirect light
	}
	return (directL + globalL + causticsL) * W;

}

Real PhotonMapping::distance(const Vector3& v1, const Vector3& v2)const
{
	return sqrt(
		pow(v1[0] - v2[0], 2) +
		pow(v1[1] - v2[1], 2) +
		pow(v1[2] - v2[2], 2));
}

Vector3 PhotonMapping::cone_kernel(std::vector<const KDTree<Photon, 3U>::Node*> photons, Intersection it, Real radius, Real k, bool BRDF_at_indirect)const
{
	Vector3 light;
	Vector3 Wp;
	for each (const KDTree<Photon, 3U>::Node* photon_node in photons) {
		Wp = std::max(0.0f, 1 - distance(photon_node->data().position, it.get_position()) / (k * radius));
		if (BRDF_at_indirect) {
			light += (it.intersected()->material()->get_albedo(it) / M_PI) * photon_node->data().flux * Wp;
		}
		else {
			light += photon_node->data().flux * Wp;
		}
	}
	return light / ((1 - (2 / (3 * k))) * (M_PI * radius * radius));
}

void PhotonMapping::fix_near_photons(const std::vector<const KDTree<Photon, 3U>::Node*> photons, const Intersection it,
	std::vector<const KDTree<Photon, 3U>::Node*> &photons_fix, Real &radius)const {
	radius = 0;
	Real tmp_distance;
	for each (const KDTree<Photon, 3U>::Node* photon_node in photons)
	{
		if (dot(photon_node->data().direction, it.get_normal()) < 0) {
			tmp_distance = distance(photon_node->data().position, it.get_position());
			if (tmp_distance > radius) {
				radius = tmp_distance;
			}
			photons_fix.push_back(photon_node);
		}
	}
}