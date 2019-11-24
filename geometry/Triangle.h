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

    Vector get_centroid() const;
    float get_min_X() const;
    float get_max_X() const;
    float get_min_Y() const;
    float get_max_Y() const;
    float get_min_Z() const;
    float get_max_Z() const;

private:
    float get_min(int position) const;
    float get_max(int position) const;

};


#endif //COMPUTERGRAPHICS_TRIANGLE_H
