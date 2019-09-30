/**
 * The class sphere represents a sphere in 3d, defined by a point in space and a radius
 */

#ifndef COMPUTERGRAPHICS_SPHERE_H
#define COMPUTERGRAPHICS_SPHERE_H


#include <Vector.h>
#include "Ray.h"

class Sphere {
private:
    Vector center;
    float radius;

public:
    Sphere();
    Sphere(const Vector &center, const float radius);

    Vector getN(const Vector &collisionPoint) const;
    // Intersection between Ray and Sphere
    bool intersection(const Ray &r, float &t);
    const Vector &getCenter() const;
    void setCenter(const Vector &center);
    float getRadius() const;
    void setRadius(float radius);

    friend std::ostream &operator<<(std::ostream &os, const Sphere &sp);

};


#endif //COMPUTERGRAPHICS_SPHERE_H
