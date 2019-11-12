//
// Created by Sergio on 08/11/2019.
//

#ifndef COMPUTERGRAPHICS_COLLISIONOBJECT_H
#define COMPUTERGRAPHICS_COLLISIONOBJECT_H

#include "Ray.h"
#include "../imaging/RGB.h"

/**
 * An abstract class that represents any object that can be collided with lightning.
 */
class CollisionObject{
public:
    virtual bool intersection(const Ray &ray, float &t) = 0;
    virtual Vector get_normal(const Vector& collision_point) const = 0;
    virtual RGB get_color_emitter() = 0;
};

#endif //COMPUTERGRAPHICS_COLLISIONOBJECT_H
