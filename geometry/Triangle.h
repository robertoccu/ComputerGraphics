//
// Created by Sergio on 12/11/2019.
//

#ifndef COMPUTERGRAPHICS_TRIANGLE_H
#define COMPUTERGRAPHICS_TRIANGLE_H


#include "CollisionObject.h"
#include "Plane.h"

class Triangle : public CollisionObject{
private:
    Vector a, b, c;
    Vector normal;
public:
    Triangle(const Vector &a, const Vector &b, const Vector &c);
    bool intersection(const Ray &ray, float &t) override;

    Vector get_normal(const Vector &collision_point) const override ;
    void set_normal(const Vector &normal);
};


#endif //COMPUTERGRAPHICS_TRIANGLE_H
