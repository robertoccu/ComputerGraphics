
#include "Plane.h"

Plane::Plane(const Vector &point, const Vector &normal) : point(point),
                                                                              normal(normal){
    distance = - (Vector::dot(normal, point));
}

Plane::Plane() = default;

bool Plane::intersection(const Ray &ray, float &t) {
    bool is_intersection = false;
    float dot_product = Vector::dot(normal, ray.getDirection());
    if(dot_product != 0){
        is_intersection = true;
        t = -(distance + Vector::dot(ray.getOrigin(), normal)) / dot_product;
    }else{
        is_intersection = false;
    }
    return is_intersection;
}

Vector Plane::get_normal(const Vector &collision_point) const {
    return normal;
}