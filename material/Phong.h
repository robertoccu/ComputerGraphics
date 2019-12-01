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
        // Not in use. See get_outgoing_ray.
        /*RGB brdf;
        //Vector Wr = 2 * normal * Vector::dot(out_ray.getDirection(), normal) - out_ray.getDirection();
        Vector Wr = in_ray.getDirection() - 2 * (in_ray.getDirection() - normal * Vector::dot(in_ray.getDirection(), normal));
        Wr = Wr.normalize();
        float cosine = Vector::dot(in_ray.getDirection(), Wr);
        // Calculate the Phong BRDF
        brdf = Kd + Ks * ((Ns + 2) * 0.5) * pow(abs(cosine), Ns);
        //cout<<brdf<<endl;
        // Now divide by the pdf
        float prr = Kd.get_max_color() + Ks.get_max_color();
        RGB color = brdf * (1 / prr);
        return color;*/
        return RGB(-1,-1,-1);
    }

    RGB get_outgoing_ray(const Ray& in_ray, const Vector& collision_normal, const Vector& collision_point, Ray& out_ray, float rr) {
        float epsilon = 1.5;

        if (rr < Kd.get_max_color()) {
            // // Diffuse
            // Get random angles from inverse cumulative probability function (c^-1)
            float r_theta = Prng::random();
            float r_phi   = Prng::random();
            float theta = acos(sqrt(1-r_theta));
            float phi = 2 * M_PI * r_phi;

            // Calculate reflected ray in local coordinates
            Vector w(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta), VEC);

            // Change reflected ray from local to global coordinates
            Matrix T;
            Vector Vec1 = collision_normal.perpendicular().normalize();
            Vector Vec2 = Vector::cross(collision_normal, Vec1).normalize();
            Vector Vec3 = collision_normal.normalize();
            T.setVector(Vec1,0);
            T.setVector(Vec2,1);
            T.setVector(Vec3,2);
            T.setPoint(collision_point);
            Vector out_dir = T * w; out_dir = out_dir.normalize();

            // Outgoing ray
            out_ray = Ray(collision_point + (out_dir.normalize() * epsilon), out_dir);

            // BRDF in this point
            RGB brdf = Kd;
            brdf = brdf * (1/Kd.get_max_color());
            return brdf;
        } else if (rr < Kd.get_max_color() + Ks.get_max_color()) {
            // // Specular
            // Matrix to chage from local at collision_point to global.
            Matrix T;
            Vector Vec1 = collision_normal.perpendicular().normalize();
            Vector Vec2 = Vector::cross(collision_normal, Vec1).normalize();
            Vector Vec3 = collision_normal.normalize();
            T.setVector(Vec1,0);
            T.setVector(Vec2,1);
            T.setVector(Vec3,2);
            T.setPoint(collision_point);

            // Change in_ray to local coordinates
            Vector in_dir = T.inverse() * in_ray.getDirection();

            // Calculate reflected ray in local coordinates. Perfect reflection.
            Vector w(-in_dir.get(0),-in_dir.get(1),in_dir.get(2), VEC);

            // Change reflected ray from local to global coordinates
            Vector out_dir = T * w;

            // Outgoing ray
            out_ray = Ray(collision_point + (out_dir.normalize() * epsilon), out_dir);

            // BRDF in this point
            RGB brdf = Ks * ((Ns + 2.0) * 0.5) * pow(abs(Vector::dot(in_dir, w)), Ns);
            brdf = brdf * (1 / Ks.get_max_color());
            return brdf;
        } else {
            return RGB(-1,-1,-1);
        }

        /*float r_theta = Prng::random();
        float r_phi   = Prng::random();

        float theta = acos(sqrt(1-r_theta));
        float phi = 2 * M_PI * r_phi;

        Vector w(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta), VEC);
        Matrix T;
        Vector Vec1 = collision_normal.perpendicular().normalize();
        Vector Vec2 = Vector::cross(collision_normal, Vec1).normalize();
        Vector Vec3 = collision_normal.normalize();
        T.setVector(Vec1,0);
        T.setVector(Vec2,1);
        T.setVector(Vec3,2);
        T.setPoint(collision_point);

        if (abs(Vector::dot(Vec1, Vec2)) > 0.01 || abs(Vector::dot(Vec1, Vec3)) > 0.01 || abs(Vector::dot(Vec2, Vec3)) > 0.01) {
            cout << "A: " << abs(Vector::dot(Vec1, Vec2)) << "B: " << abs(Vector::dot(Vec1, Vec3)) << "C: " << abs(Vector::dot(Vec2, Vec3)) << endl;
        }

        Vector out_dir = T * w; out_dir = out_dir.normalize();
        float epsilon = 0.1;
        out_ray = Ray(collision_point + (out_dir * epsilon), out_dir);

        return get_BRDF(in_ray, collision_normal, out_ray);*/
    }

    RGB get_BRDF_next_event(const Ray &in_ray, const Vector &normal, const Ray &shadow_ray, const DotLight light,
            const Vector& collision_point) const override {
        // Lo = p / d^2 * fr(x, shadow_ray, in_ray) * |dot(n, shadow_ray)|
        RGB evaluate_render_equation;
        Vector Wr = 2 * normal * (shadow_ray.getDirection() * normal) - shadow_ray.getDirection();
        Wr = Wr.negate(); Wr = Wr.normalize();
        RGB dot_light_in_point = light.light_in_the_point(collision_point);
        RGB brdf_next = (Kd * M_1_PI) + (Ks * (Ns + 2) * M_2_PI) * pow(abs(Vector::dot(in_ray.getDirection(), Wr)), Ns);
        float cosine = abs(Vector::dot(normal, shadow_ray.getDirection()));
        evaluate_render_equation = dot_light_in_point * brdf_next * cosine;
        return evaluate_render_equation;
    }

};
#endif //COMPUTERGRAPHICS_PHONG_H
