/**
 * The class sphere represents a sphere in 3d, defined by a point in space and a radius
 */

#ifndef COMPUTERGRAPHICS_SPHERE_H
#define COMPUTERGRAPHICS_SPHERE_H


#include <Vector.h>
#include "Ray.h"
#include "CollisionObject.h"

class Sphere : public CollisionObject{
private:
    Vector center;
    float radius;
    RGB emision;

public:
    Sphere();
    Sphere(const Vector &center, float radius);
    const Vector &getCenter() const;
    void setCenter(const Vector &center);
    float getRadius() const;
    void setRadius(float radius);

    // Funciones heredadas
    bool intersection(const Ray &r, float &t);
    Vector get_normal(const Vector &collisionPoint) const;

    // DEBUG
    void setEmision(const RGB& emision){this->emision = emision;}
    RGB getEmision(){return this->emision;}

    


    friend std::ostream &operator<<(std::ostream &os, const Sphere &sp);

};


#endif //COMPUTERGRAPHICS_SPHERE_H
