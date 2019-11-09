//
// Created by Sergio on 27/09/2019.
//

#include <iostream>
#include <iomanip>
#include "Ray.h"

/**
 * Default constructor
 */
Ray::Ray() {
    origin = direction = Vector();
}

/**
 * Constructor with a origin point and a direction vector
 * @param origin point origin
 * @param direction direction vector
 */
Ray::Ray(const Vector &origin, const Vector &direction) {
    this->origin = origin;
    this->direction = direction;
}

/**
 * Constructor of a ray that goes from a point of origin to a point of destination.
 * @param origin origin point
 * @param end end point
 * @return
 */
Ray Ray::rayFromPoints(const Vector &origin, const Vector &end) const {
    return Ray(origin, (end - origin).normalize());
}

const Vector &Ray::getOrigin() const {
    return origin;
}

void Ray::setOrigin(const Vector &origin) {
    Ray::origin = origin;
}

const Vector &Ray::getDirection() const {
    return direction;
}

void Ray::setDirection(const Vector &direction) {
    Ray::direction = direction;
}


/**
 * Gets the resulting point from moving the origin point "t" units in the direction of the vector
 * @param t t units to move
 * @return point
 */
Vector Ray::operator*(const float t) const {
    return this->origin + t * this->direction;
}

/**
 * Shows on screen the vector with a defined format. Each component of the vector in a different row
 * @param os
 * @param v1
 * @return the output screen
 */
std::ostream &operator<<(std::ostream &os, const Ray &r){
    os << std::fixed;
    os << std::setprecision(2);     // Number of decimals

    os << std::setw(7)<<"     Origin"<<"\t"<<"Direction"<<std::endl;
    os << std::setw(7)<<"x: "<<r.origin.get(0)<<"\t"<<r.direction.get(0)<<std::endl;
    os << std::setw(7)<<"y: "<<r.origin.get(1)<<"\t"<<r.direction.get(1)<<std::endl;
    os << std::setw(7)<<"z: "<<r.origin.get(2)<<"\t"<<r.direction.get(2)<<std::endl;
    os << std::setw(7)<<"w: "<<r.origin.get(3)<<"\t"<<r.direction.get(3)<<std::endl;

    return os;
}
