//
// Created by Sergio on 26/11/2019.
//

#ifndef COMPUTERGRAPHICS_SPECULARPERFECT_H
#define COMPUTERGRAPHICS_SPECULARPERFECT_H

#include "Material.h"
#include "../geometry/Ray.h"

class SpecularPerfect : public Material{
private:
    RGB Ksp;
public:
    SpecularPerfect(const RGB& color) : Ksp(color){
        this->set_material(material_type::SPECULAR);
    }

    RGB get_emision() override {
        return RGB();
    }

    RGB get_BRDF(const Ray& in_ray, const Vector& normal, Ray& out_ray){
        return Ksp;
    }

    RGB get_outgoing_ray(const Ray &in_ray, const Vector &collision_normal, const Vector &collision_point, Ray &out_ray,
                         float rr) {
        // Calculate the reflected ray with the law Wr = Wi - 2(Wi - n(Wi,n))
        Vector Wr = in_ray.getDirection() - 2 * (in_ray.getDirection() - collision_normal * Vector::dot(in_ray.getDirection(), collision_normal));
        Wr = Wr.normalize();
        // Now normalize by the Wi and N
        Wr = Wr / Vector::dot(in_ray.getDirection(), collision_normal);
        // Divide by the probability this event
        Wr = Wr / Ksp.get_max_color();
        // Asign the out_dir
        Wr = Wr.normalize();
        out_ray = Ray(collision_point + (0.1 * Wr), Wr);
        return Ksp;
    }

    RGB get_BRDF_next_event(const Ray &in_ray, const Vector &normal, const Ray &shadow_ray, const DotLight light,
                            const Vector &collision_point) const override {
        return RGB(0,0,0);
    }
};


#endif //COMPUTERGRAPHICS_SPECULARPERFECT_H
