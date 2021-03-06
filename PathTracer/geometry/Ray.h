/**
 * A ray is defined as a starting point from which the ray departs, and a vector direction.
 */
#ifndef COMPUTERGRAPHICS_RAY_H
#define COMPUTERGRAPHICS_RAY_H

#include "../maths/Vector.h"

class Ray {
private:
    Vector origin;
    Vector direction;
    bool refracted = false;
public:
    Ray();
    Ray(const Vector &origin, const Vector &direction);
    Ray(const Vector &origin, const Vector &direction, const bool refracted);
    Ray rayFromPoints(const Vector &origin, const Vector &end) const;

    // Setter and getter
    const Vector &getOrigin() const;
    void setOrigin(const Vector &origin);
    const Vector &getDirection() const;
    void setDirection(const Vector &direction);
    const bool has_been_refracted() const;

    Vector operator*(const float t) const;

    friend std::ostream &operator<<(std::ostream &os, const Ray &r);
};


#endif //COMPUTERGRAPHICS_RAY_H
