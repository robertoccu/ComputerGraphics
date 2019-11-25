//
// Created by Sergio on 08/11/2019.
//

#ifndef COMPUTERGRAPHICS_MATERIAL_H
#define COMPUTERGRAPHICS_MATERIAL_H

#include "../imaging/RGB.h"

enum material_type{EMITTER, PHONG};
/**
 * Abstract class that represents all possible materials. Lambertian, perfect specular...etc.
 * TODO: Implement it and add it to the collisionObject class
 */
class Material{
private:
    material_type material;
public:
    void set_material(material_type mat){ this->material = mat;}
    material_type get_material(){ return material;}

    virtual RGB get_emision() = 0;
    virtual RGB get_BRDF(const Ray& in_ray, const Vector& normal, Ray& out_ray) = 0;
    virtual RGB get_outgoing_ray(const Ray& in_ray, const Vector& collision_normal, const Vector& collision_point, Ray& out_ray, float rr) = 0;
};

#endif //COMPUTERGRAPHICS_MATERIAL_H
