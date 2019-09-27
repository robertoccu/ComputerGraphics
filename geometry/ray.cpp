//
// Created by Sergio on 27/09/2019.
//

#include <iostream>
#include <iomanip>
#include "ray.h"

/**
 * Default constructor
 */
ray::ray() {
    origin = direction = Vector();
}

/**
 * Constructor with a origin point and a direction vector
 * @param origin point origin
 * @param direction direction vector
 */
ray::ray(const Vector &origin, const Vector &direction) {
    this->origin = origin;
    this->direction = direction;
}

/**
 * Constructor of a ray that goes from a point of origin to a point of destination.
 * @param origin origin point
 * @param end end point
 * @return
 */
ray ray::rayFromPoints(const Vector &origin, const Vector &end) const {
    return ray(origin, end-origin);
}

const Vector &ray::getOrigin() const {
    return origin;
}

void ray::setOrigin(const Vector &origin) {
    ray::origin = origin;
}

const Vector &ray::getDirection() const {
    return direction;
}

void ray::setDirection(const Vector &direction) {
    ray::direction = direction;
}


/**
 * Gets the resulting point from moving the origin point "t" units in the direction of the vector
 * @param t t units to move
 * @return point
 */
Vector ray::operator*(const float t) const {
    return this->origin + t * this->direction;
}

/**
 * Shows on screen the vector with a defined format. Each component of the vector in a different row
 * @param os
 * @param v1
 * @return the output screen
 */
std::ostream &operator<<(std::ostream &os, const ray &r){
    os << std::fixed;
    os << std::setprecision(2);     // Number of decimals

    os << std::setw(7)<<"     Origin"<<"\t"<<"Direction"<<std::endl;
    os << std::setw(7)<<"x: "<<r.origin.get(0)<<"\t"<<r.direction.get(0)<<std::endl;
    os << std::setw(7)<<"y: "<<r.origin.get(1)<<"\t"<<r.direction.get(1)<<std::endl;
    os << std::setw(7)<<"z: "<<r.origin.get(2)<<"\t"<<r.direction.get(2)<<std::endl;
    os << std::setw(7)<<"w: "<<r.origin.get(3)<<"\t"<<r.direction.get(3)<<std::endl;

    return os;
}
