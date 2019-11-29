/*#ifndef COMPUTERGRAPHICS_COMPOSITE_H
#define COMPUTERGRAPHICS_COMPOSITE_H


#include "Material.h"
#include "Emitter.h"
#include "Phong.h"

/**
 * Represents a material composed of Phong,
 * Emission, Specular Perfect and Refraction perfect.
 */
/*class Composite : public Material{
    Emitter emitter;
    Phong phong;
    // TODO: SPECULAR PERFECT AND REFRACTION PERFECT
public:
    Composite(const Emitter& emitter, const Phong &phong){this->emitter = emitter; this->phong = phong;}
    Composite() {emitter = Emitter(); phong = Phong();}
    RGB get_emision() override{ return emitter.get_emision(); }
    RGB get_BRDF(const Ray& in_ray, const Vector& normal, Ray& out_ray) override{return RGB();}
    RGB get_outgoing_ray(const Ray& in_ray, const Vector& collision_normal, const Vector& collision_point, Ray& out_ray, float rr) override{return RGB();}

    RGB get_BRDF_next_event(const Ray &in_ray, const Vector &normal, const Ray &shadow_ray, const DotLight light,
                            const Vector &collision_point) const override {
        return RGB(0,0,0);
    }
};
#endif //COMPUTERGRAPHICS_COMPOSITE_H
*/