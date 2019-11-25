//
// Created by Sergio on 19/11/2019.
//

#ifndef COMPUTERGRAPHICS_PHONG_H
#define COMPUTERGRAPHICS_PHONG_H

#include "Material.h"

/**
 * Represent an material phong
 */
class Phong : public Material{
private:
    RGB Kd, Ks; // Difuse and Specular
    float Ns; // Shinnies
public:
    Phong(const RGB &kd, const RGB &ks, const float &ns) : Kd(kd), Ks(ks), Ns(ns) {
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
    RGB get_BRDF(const Ray& in_ray, Ray& out_ray) override{
        RGB brdf;
        // Calculate the Phong BRDF
        brdf = 2 * Kd + Ks * (Ns + 2) * Vector::dot(in_ray.getDirection(), out_ray.getDirection());
        // Now divide by the pdf
        float pdf = (Kd.get_mean_color() + Ks.get_mean_color()) / 2;
        return brdf * (1 / pdf);
    }

    RGB get_outgoing_ray(const Ray& ray, Ray& out_ray, float rr) {
        static std::random_device rd;
        static std::mt19937 mt(rd());
        static std::uniform_real_distribution<float> dist(0.0, 1.0);

        float r_theta = dist(mt);
        float r_phi = dist(mt);

        float c_theta = acos(sqrt(1-r_theta));
        float c_phi = 2 * M_PI * r_phi;

        //TODO: Generate ray
    }
};
#endif //COMPUTERGRAPHICS_PHONG_H
