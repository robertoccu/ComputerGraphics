//
// Created by Sergio on 23/11/2019.
//

#include <cmath>
#include "AABB.h"

AABB::AABB(const Vector &less, const Vector &greater) {
    this->min_point = less;
    this->max_point = greater;
}

/**
 * De momento solo devolvemos true o falso
 * https://tavianator.com/fast-branchless-raybounding-box-intersections-part-2-nans/
 * @param ray
 * @param t
 * @return
 */
bool AABB::intersection(const Ray &ray, float &t) {
    const Vector& inverse = ray.getInverseDirection();

    float tmin = -INFINITY, tmax = INFINITY;
    float t1, t2;
    for(int dim = 0; dim < 3; dim++){
        t1 = (min_point.get(dim) - ray.getOrigin().get(dim)) * inverse.get(dim);
        t2 = (max_point.get(dim) - ray.getOrigin().get(dim)) * inverse.get(dim);
        tmin = max(tmin, min(t1, t2));
        tmax = min(tmax, max(t1, t2));
    }
    return tmax >= max(tmin, 0.0f);
}

Vector AABB::get_normal(const Vector &collision_point) const {
    return Vector();
}

AABB::AABB(const Triangle &tr) {
    this->min_point = Vector(tr.get_min_X(), tr.get_min_Y(), tr.get_min_Z(), 1);
    this->max_point = Vector(tr.get_max_X(), tr.get_max_Y(), tr.get_max_Z(),1);
}

bool AABB::comparator(const AABB &aabb1, const AABB &aabb2, int axis) {
    return aabb1.getCentroid().get(axis) < aabb2.getCentroid().get(axis);
}

bool AABB::comparatorX(const AABB &aabb1, const AABB &aabb2) {
    return comparator(aabb1, aabb2, 0);
}

bool AABB::comparatorY(const AABB &aabb1, const AABB &aabb2) {
    return comparator(aabb1, aabb2, 1);
}

bool AABB::comparatorZ(const AABB &aabb1, const AABB &aabb2) {
    return comparator(aabb1, aabb2, 2);
}
