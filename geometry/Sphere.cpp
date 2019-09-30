//
// Created by Sergio on 27/09/2019.
//

#include <cmath>
#include "Sphere.h"

/**
 * Default constructor
 */
Sphere::Sphere() {
    center = Vector(0,0,0,1);
    radius = 0;
}

/**
 * Constructor by a center point and a radius
 * @param center origin
 * @param radius radius of the sphere
 */
Sphere::Sphere(const Vector &center, const float radius) {
    this->center = center;
    this->radius = radius;
}

/**
 * It returns true if and the ray intersects with the sphere at some point in space.
 * If true, the variable t returns the distance from the point of the ray to the point of collision.
 * If it is false, in the variable t returns 0.
 * @param r
 * @param t
 * @return
 */
bool Sphere::intersection(const Ray &r, float &t) {
    bool is_intersected = false;
    t = 0;
    // Ray   =>  P = O + tD
    // Sphere => (P - C)*(P - C) -r^2 = 0
    // ((O + tD) - C)*((O + tD) - C) -r^2 = 0
    float a = r.getDirection() * r.getDirection();  // D ^ 2
    float b = 2 * ((r.getOrigin() * r.getDirection()) - (r.getDirection() * this->getCenter()));
    float c = (r.getOrigin() * r.getOrigin()) - (2 * (r.getOrigin() * this->getCenter()))
            + (this->getCenter()*this->getCenter());
    c = c - (this->getRadius() * this->getRadius());

    // Calculation of the second-degree equation discriminant
    float discriminant = (b * b) - (4 * a *c);
    if(discriminant < 0) {
        // Negative solution
        t = 0;
        return false;   // No solution
    }
    else {
        // Being a second-degree equation and the root is positive, it has two solutions
        float op1 = (-b + sqrtf(discriminant)) / 2*a;
        float op2 = (-b - sqrtf(discriminant)) / 2*a;

        // Choose the minor t
        if(op1 < 0 && op2 < 0) {
            // two options is negative, no intersection
            t = 0;
        }else if(op1 > 0 && op2 < 0) {
            // One positive, other negative choose positive
            t = op1;
            is_intersected = true;
        }else if(op1 < 0 && op2 > 0) {
            t = op2;
            is_intersected = true;
        }else {
            // Two are positive, we choose the minor
            t = (op1 > op2) ? op2 : op1;
            is_intersected = true;
        }
    }

    return is_intersected;
}

/**
 * Returns the normal vector of the surface to the collision point.
 * @param collisionPoint
 * @return normal vector
 */
Vector Sphere::getN(const Vector &collisionPoint) const{
    return collisionPoint - this->center;
}

const Vector &Sphere::getCenter() const {
    return center;
}

void Sphere::setCenter(const Vector &center) {
    Sphere::center = center;
}

float Sphere::getRadius() const {
    return radius;
}

void Sphere::setRadius(float radius) {
    Sphere::radius = radius;
}

std::ostream &operator<<(std::ostream &os, const Sphere &sp) {
    os << "Sphere"<<std::endl;
    os <<" \tCenter: [";
    for(int i = 0; i < 4; i++){
        if(i == 3){
            os <<sp.center.get(i)<<"]\n";
        }else{
            os <<sp.center.get(i)<<", ";
        }
    }
    os <<" \tRadius: "<< sp.radius<<std::endl;

    return os;
}
