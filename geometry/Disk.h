
#ifndef COMPUTERGRAPHICS_DISK_H
#define COMPUTERGRAPHICS_DISK_H


#include "CollisionObject.h"
#include "Plane.h"

class Disk : public CollisionObject{
private:
    Vector center;
    Plane plane;
    float radius;

public:
    Disk(const Vector &center, const Plane &plane, float radius);

    bool intersection(const Ray &ray, float &t) override;

    Vector get_normal(const Vector &collision_point) const override ;
};


#endif //COMPUTERGRAPHICS_DISK_H
