#ifndef COMPUTERGRAPHICS_COMPOSITE_H
#define COMPUTERGRAPHICS_COMPOSITE_H


#include "Material.h"
#include "Emitter.h"
#include "Phong.h"
#include "SpecularPerfect.h"
#include "RefractionPerfect.h"

/**
 * Represents a material composed of Phong,
 * Emission, Specular Perfect and Refraction perfect.
 */
class Composite : public Material{
    Emitter emitter;
    Phong phong;
    SpecularPerfect specular;
    RefractionPerfect refraction;
public:
    Composite(const Emitter &emitter, const Phong &phong, const RefractionPerfect refraction, const SpecularPerfect specular)
            : emitter(emitter), phong(phong), refraction(refraction), specular(specular) {
        this->set_material(material_type::REFRACTION);
    }
    Composite() {emitter = Emitter(); phong = Phong(); refraction = RefractionPerfect(); specular = SpecularPerfect();
        this->set_material(material_type::REFRACTION);}

    RGB get_emision() override{ return emitter.get_emision(); }

    RGB get_BRDF(const Ray& in_ray, const Vector& normal, Ray& out_ray) override{ return RGB();}

    RGB get_outgoing_ray(const Ray& in_ray, const Vector& collision_normal, const Vector& collision_point, Ray& out_ray, float rr) override{

        float phong_probability = this->get_Kd().get_max_color() + this->get_Ks().get_max_color();
        float specular_probability = this->get_Ksp().get_max_color() + phong_probability;
        float refraction_probability = this->get_Kr().get_max_color() + specular_probability;

        if(rr <= phong_probability){
            return phong.get_outgoing_ray(in_ray, collision_normal, collision_point, out_ray, rr);
        }else if(rr > phong_probability && rr <= specular_probability){
            return specular.get_outgoing_ray(in_ray, collision_normal, collision_point, out_ray, rr);
        }else if(rr > specular_probability && rr <= refraction_probability){
            return refraction.get_outgoing_ray(in_ray, collision_normal, collision_point, out_ray, rr);
        }else{
            return RGB(0,0,0);
        }
    }

    RGB get_BRDF_next_event(const Ray &in_ray, const Vector &normal, const Ray &shadow_ray, const DotLight light,
                            const Vector &collision_point) const override {
        if(get_Kd().get_max_color() > 0 || get_Ks().get_max_color() > 0){
            // Only for phong materials
            return phong.get_BRDF_next_event(in_ray, normal, shadow_ray, light, collision_point);
        }else{
            return RGB(0,0,0);
        }
    }

    RGB get_Kd() const override {
        return phong.get_Kd();
    }

    RGB get_Ks() const override {
        return phong.get_Ks();
    }

    RGB get_Ksp() const override {
        return specular.get_Ksp();
    }

    RGB get_Kr() const override {
        return refraction.get_Kr();
    }
};
#endif //COMPUTERGRAPHICS_COMPOSITE_H
