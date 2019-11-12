#ifndef COMPUTERGRAPHICS_PLANE_H
#define COMPUTERGRAPHICS_PLANE_H

#include <memory>
#include "../maths/Vector.h"
#include "CollisionObject.h"
#include "../material/Material.h"

/**
 * Object that defines a plane. A plane is defined by a vector normal to the surface and by a distance to the origin
 */
class Plane : public CollisionObject{
    Vector point;           // Point of plane
    Vector normal;       // Normal direction of plane
    float distance;           // Origin distance

public:
    Plane(const Vector &point, const Vector &normal);
    Plane();

    bool intersection(const Ray &ray, float &t) override;

    Vector get_normal(const Vector &collision_point) const override ;

};


#endif //COMPUTERGRAPHICS_PLANE_H
