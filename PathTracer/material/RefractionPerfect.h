//
// Created by Sergio on 26/11/2019.
//

#ifndef COMPUTERGRAPHICS_REFRACTIONPERFECT_H
#define COMPUTERGRAPHICS_REFRACTIONPERFECT_H

#include <math.h>
#include <algorithm>
#include "Material.h"
#include "../geometry/Ray.h"

enum refraction_type{WATER, GLASS, AIR, DIAMOND};

class RefractionPerfect : public Material{
private:
    RGB Kr;
    float ri;
public:
    RefractionPerfect(const RGB& color) : Kr(color){
        this->set_material(material_type::REFRACTION);
    }

    void set_type(refraction_type refraction){
        switch(refraction){
            case WATER:     this->ri = 1.333f; break;
            case GLASS:     this->ri = 1.520f; break;
            case AIR:       this->ri = 1.000f; break;
            case DIAMOND:   this->ri = 2.417f; break;
        }
    }

    RefractionPerfect() : Kr(RGB(0,0,0)){
        this->set_material(material_type::REFRACTION);
    }

    RGB get_emision() override {
        return RGB();
    }

    RGB get_BRDF(const Ray& in_ray, const Vector& normal, Ray& out_ray){
        return Kr;
    }

    RGB get_outgoing_ray(const Ray &in_ray, const Vector &collision_normal, const Vector &collision_point, Ray &out_ray,
                         float rr) override {
        float epsilon = 0.001;
        Vector out_dir;
        bool refracted = in_ray.has_been_refracted();
        bool inside = refracted;
        if (inside) {
            refracted = refracted_direction(in_ray.getDirection().normalize(), collision_normal.normalize(),
                                                ri, 1.000293f, out_dir);
            inside = !refracted;
        } else {
            refracted = refracted_direction(in_ray.getDirection().normalize(), collision_normal.normalize(),
                                                1.000293f, 	ri, out_dir);
            inside = refracted;
        }

        out_ray = Ray(collision_point + (out_dir.normalize() * epsilon), out_dir.normalize(), inside);
        return Kr;
    }

    RGB get_BRDF_next_event(const Ray& in_ray, const Vector& normal, const Ray& shadow_ray, const DotLight light,
                            const Vector& collision_point) const override{
        return RGB(0,0,0);
    }

    /**
     * If the ray is refracted, return true and v_out contain the refracted ray.
     * If the ray is not refracted(total internal reflection), return false and v_out contain the reflect ray.
     * For more info visit: https://en.wikipedia.org/wiki/Snell%27s_law
     * @param v_in incident ray NORMALIZED!
     * @param normal_surface normal at surface NORMALIZED!
     * @param ior1 index of refraction from the extern material
     * @param ior2 index of refraction from the internal material
     * @param v_out ray refracted or reflect
     * @return true if the ray is refracted, false if the ray is reflect
     */
    bool refracted_direction(const Vector& v_in, const Vector& normal_surface, float ri_from, float ri_to,
                             Vector& v_out){
        /*float dt = Vector::dot(v_in, normal_surface);   // Angle between in and normal
        float ior1_over_ior2 = ior1 / ior2; // Proportion to ior1 and ior2
        float discriminant = 1.0f - ior1_over_ior2 * ior1_over_ior2 * (1 - dt * dt);
        if(discriminant > 0){
            // Return refracted ray
            v_out = ior1_over_ior2 * (v_in - normal_surface * dt) - normal_surface * sqrtf(discriminant);
            return true;
        }else{
            // Return reflected ray
            v_out = v_in - 2 * Vector::dot(v_in, normal_surface) * normal_surface;
            return false;
        }*/

        Vector normal = normal_surface;
        float ior1_over_ior2 = ri_from / ri_to;
        float cos_in_n = Vector::dot(normal.negate(), v_in);
        if (cos_in_n < 0) {
            normal = normal.negate();
            cos_in_n = Vector::dot(normal.negate(), v_in);
        }
        Vector v_refl = v_in + 2 * cos_in_n * normal;

        float cos_o2 = sqrtf(1 - pow(ior1_over_ior2, 2) * (1 - pow(cos_in_n, 2)));

        Vector v_refr = ior1_over_ior2 * v_in + (ior1_over_ior2 * cos_in_n - cos_o2) * normal;

        v_out = v_refr;
        return true;
    }

    RGB get_Kr() const override {
        return Kr;
    }
};


#endif //COMPUTERGRAPHICS_SPECULARPERFECT_H
