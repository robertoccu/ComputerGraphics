#include "Triangle.h"

Triangle::Triangle(const Vector &a, const Vector &b, const Vector &c) {
    this->a = a;
    this->b = b;
    this->c = c;

    // Vectors to construct the plane to obtain the normal
    Vector vBA = Vector(b.get(0),b.get(1),b.get(2),1);
    vBA = vBA - Vector(a.get(0),a.get(1),a.get(2),1);
    Vector vCA = Vector(c.get(0),c.get(1),c.get(2),1);
    vCA = vCA - Vector(a.get(0),a.get(1),a.get(2),1);

    this->normal = Vector::cross(vBA, vCA);
    this->normal = this->normal.normalize();

}

bool Triangle::intersection(const Ray &ray, float &t) {
    bool result = false;
    // The normal at Triangle is the same that the plane
    Plane plane(a, this->normal);
    bool intersection_plane = plane.intersection(ray, t);
    // If the ray dont intesect with the plane, dont intersect with the Triangle
    if(intersection_plane){
        // Now you check if the point obtained is contained in that plane.
        // In order to do this, we will see if the point is to the right or to the left.
        Vector collision_point = ray.getOrigin() + (t * ray.getDirection());
        float s1 = Vector::dot(Vector::cross(b - a, collision_point - a), this->normal);
        float s2 = Vector::dot(Vector::cross(c - b, collision_point - b), this->normal);
        float s3 = Vector::dot(Vector::cross(a - c, collision_point - c), this->normal);

        result = !(s1 < 0 || s2 < 0 || s3 < 0);
    }

    return result;
}

Vector Triangle::get_normal(const Vector &collision_point) const {
    return normal;
}

void Triangle::set_normal(const Vector &vector) {
    this->normal = vector;
}
