//
// Created by Sergio on 23/11/2019.
//

#ifndef COMPUTERGRAPHICS_AABB_H
#define COMPUTERGRAPHICS_AABB_H


#include "CollisionObject.h"
#include "Triangle.h"

class AABB : public CollisionObject{
private:
    Vector min_point, max_point;
public:
    AABB(const Vector& less, const Vector& greater);
    AABB(const Triangle& tr);
    AABB(){}
    bool intersection(const Ray &ray, float &t) override;
    Vector get_normal(const Vector &collision_point) const override;

    const Vector &getMinPoint() const { return min_point; }
    const Vector &getMaxPoint() const { return max_point; }
    Vector getCentroid() const{
        return (min_point + max_point) / 2;
    }

    static bool comparator(const AABB& aabb1, const AABB& aabb2, int axis);
    static bool comparatorX(const AABB& aabb1, const AABB& aabb2);
    static bool comparatorY(const AABB& aabb1, const AABB& aabb2);
    static bool comparatorZ(const AABB& aabb1, const AABB& aabb2);
};


#endif //COMPUTERGRAPHICS_AABB_H
