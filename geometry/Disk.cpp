//
// Created by Sergio on 12/11/2019.
//

#include "Disk.h"

Disk::Disk(const Vector &center, const Plane &plane, float radius) {
    this->center = center;
    this->plane = plane;
    this->radius = radius;
}

/**
 * Return true if the ray intersect with the disk.
 * @param ray
 * @param t
 * @return
 */
bool Disk::intersection(const Ray &ray, float &t) {
    // If the ray collides with the plane of the disk
    if(plane.intersection(ray, t)){
        // Obtain the point in the plane surface
        Vector point = ray.getOrigin() + (t * ray.getDirection());
        // Check if the distance to that point is less than the radius
        return (point - center).modulus() <= radius;
    }else{
        return false;
    }
}

Vector Disk::get_normal(const Vector &collision_point) const {
    return plane.get_normal(collision_point);
}

RGB Disk::getEmision() {
    return color_emission;
}
