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

};

#endif //COMPUTERGRAPHICS_MATERIAL_H
