//
// Created by Sergio on 08/11/2019.
//

#ifndef COMPUTERGRAPHICS_MATERIAL_H
#define COMPUTERGRAPHICS_MATERIAL_H

#include "../imaging/RGB.h"

/**
 * Abstract class that represents all possible materials. Lambertian, perfect specular...etc.
 * TODO: Implement it and add it to the collisionObject class
 */
class Material{
public:
    virtual RGB get_emision() = 0;
};

#endif //COMPUTERGRAPHICS_MATERIAL_H
