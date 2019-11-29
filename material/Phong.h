//
// Created by Sergio on 19/11/2019.
//

#ifndef COMPUTERGRAPHICS_PHONG_H
#define COMPUTERGRAPHICS_PHONG_H

#include <Matrix.h>
#include "Material.h"
#include "../utils/Prng.h"

/**
 * Represent an material phong
 */
class Phong : public Material{
private:
    float Ns; // Shinnies
public:
    Phong(const RGB &kd, const RGB &ks, const float &ns) : Ns(ns) {
        this->Kd = kd;
        this->Ks = ks;
        set_material(material_type::PHONG);
    }

    Phong() {Phong(RGB(0,0,0),RGB(0,0,0),0);}

    RGB get_emision() override {return RGB(0,0,0);}

    const RGB &getKd() const {return Kd;}

    const RGB &getKs() const {return Ks; }

    float getNs() const {return Ns;}

    /**
     * Return the BRDF to the phong material
     * @param in_ray
     * @param out_ray
     * @return
     */
    RGB get_BRDF(const Ray& in_ray, const Vector& normal, Ray& out_ray) override{
        /*RGB brdf;
        Vector Wr = 2 * normal * Vector::dot(out_ray.getDirection(), normal) - out_ray.getDirection();
        // Calculate the Phong BRDF
        brdf = Kd + Ks * ((Ns + 2)/2) * pow(max(Vector::dot(in_ray.getDirection(), Wr), (float)0.0), Ns);
        // Now divide by the pdf
        float prr = max(Kd.get_max_color(), Ks.get_max_color());
        RGB color = brdf * (1 / prr);
        return color;*/

        Vector Wo = in_ray.getDirection().normalize();
        Vector n = normal;
        Vector Wi = out_ray.getDirection().normalize();
        float alpha = Ns;

        return (Kd/M_PI) + (Ks * ((alpha + 2.0f)/(2.0f*(float)M_PI)) * pow(abs(Vector::dot(Wo,Wi)), alpha));
    }

    Ray get_outgoing_ray(const Ray& in_ray, const Vector& collision_normal, const Vector& collision_point) override{
        float r_theta = Prng::random();
        float r_phi   = Prng::random();

        float theta = acos(sqrt(1-r_theta));
        float phi = 2.0f * (float)M_PI * r_phi;

        Vector w(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta), VEC);
        Matrix T;
        T.setVector(collision_normal.perpendicular(),0);
        T.setVector(Vector::cross(collision_normal,collision_normal.perpendicular()),1);
        T.setVector(collision_normal,2);
        T.setPoint(collision_point);

        Vector out_dir = T * w; out_dir = out_dir.normalize();
        float epsilon = 0.1;
        return Ray(collision_point + (out_dir * epsilon), out_dir);
    }

    RGB get_BRDF_next_event(const Ray &in_ray, const Vector &normal, const Ray &shadow_ray, const DotLight light,
            const Vector& collision_point) const override {
        // Lo = p / d^2 * fr(x, shadow_ray, in_ray) * |dot(n, shadow_ray)|
        RGB evaluate_render_equation;
        Vector Wr = 2 * normal * (shadow_ray.getDirection() * normal) - shadow_ray.getDirection();
        RGB dot_light_in_point = light.light_in_the_point(collision_point);
        RGB brdf_next = (Kd * M_1_PI) + (Ks * (Ns + 2) * M_2_PI) * pow(abs(Vector::dot(in_ray.getDirection(), Wr)), Ns);
        float cosine = abs(Vector::dot(normal, shadow_ray.getDirection()));
        evaluate_render_equation = dot_light_in_point * brdf_next * cosine;
        return evaluate_render_equation;
    }

    float get_rr_probability() {
        return Kd.get_max_color() + Ks.get_max_color();
    }

};
#endif //COMPUTERGRAPHICS_PHONG_H
