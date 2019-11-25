//
// Created by Sergio on 19/11/2019.
//

#ifndef COMPUTERGRAPHICS_PHONG_H
#define COMPUTERGRAPHICS_PHONG_H

#include <Matrix.h>
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
    RGB get_BRDF(const Ray& in_ray, const Vector& normal, Ray& out_ray) override{
        RGB brdf;
        Vector Wr = 2 * normal * Vector::dot(out_ray.getDirection(), normal) - out_ray.getDirection();
        // Calculate the Phong BRDF
        brdf = Kd + Ks * (Ns + 2) * (1/M_PI) * pow(abs(Vector::dot(in_ray.getDirection(), Wr)), Ns);
        // Now divide by the pdf
        float pdf = Kd.get_mean_color() + Ks.get_mean_color();
        RGB color = brdf * (1 / pdf);
        return color;
    }

    RGB get_outgoing_ray(const Ray& in_ray, const Vector& collision_normal, const Vector& collision_point, Ray& out_ray, float rr) {
        static std::random_device rd;
        static std::mt19937 mt(rd());
        static std::uniform_real_distribution<float> dist(0.0, 1.0);

        float r_theta = dist(mt);
        float r_phi = dist(mt);

        float theta = acos(sqrt(1-r_theta));
        float phi = 2 * M_PI * r_phi;

        Vector w(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta), VEC);
        Matrix T;
        T.setVector(collision_normal.perpendicular(),0);
        T.setVector(Vector::cross(collision_normal,collision_normal.perpendicular()),1);
        T.setVector(collision_normal,2);
        T.setPoint(collision_point);

        Vector out_dir = T * w; out_dir = out_dir.normalize();
        float epsilon = 0.1;
        out_ray = Ray(collision_point + out_dir * epsilon, out_dir);

        return get_BRDF(in_ray, collision_normal, out_ray);
    }
};
#endif //COMPUTERGRAPHICS_PHONG_H
