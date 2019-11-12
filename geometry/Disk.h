
#ifndef COMPUTERGRAPHICS_DISK_H
#define COMPUTERGRAPHICS_DISK_H


#include "CollisionObject.h"
#include "Plane.h"

class Disk : public CollisionObject{
private:
    Vector center;
    Plane plane;
    float radius;
    RGB color_emission;

public:
    Disk(const Vector &center, const Plane &plane, float radius);

    bool intersection(const Ray &ray, float &t) override;

    Vector get_normal(const Vector &collision_point) const override ;

    RGB getEmision() override;
    void setEmision(const RGB &emision){this->color_emission = emision;}
};


#endif //COMPUTERGRAPHICS_DISK_H
