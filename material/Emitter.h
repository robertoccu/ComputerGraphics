#ifndef COMPUTERGRAPHICS_EMITTER_H
#define COMPUTERGRAPHICS_EMITTER_H

#include "Material.h"
#include "../imaging/RGB.h"

/**
 * Represent an object that produce emission of light.
 */
class Emitter : public Material{
    RGB emitter_color;
public:
    Emitter(const RGB &rgb){emitter_color = rgb; set_material(material_type::EMITTER);}

    Emitter() {Emitter(RGB(0,0,0));}

    RGB get_emision(){ return emitter_color;}
    RGB get_BRDF(const Ray& in_ray, const Vector& normal, Ray& out_ray) override{return RGB();}
    Ray get_outgoing_ray(const Ray& in_ray, const Vector& collision_normal, const Vector& collision_point) {
        return Ray();
    }

    RGB get_BRDF_next_event(const Ray &in_ray, const Vector &normal, const Ray &shadow_ray, const DotLight light,
                            const Vector &collision_point) const override {
        return RGB(0,0,0);
    }

    float get_rr_probability() {return 0;}

};

#endif //COMPUTERGRAPHICS_EMITTER_H
