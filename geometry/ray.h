/**
 * A ray is defined as a starting point from which the ray departs, and a vector direction.
 */
#ifndef COMPUTERGRAPHICS_RAY_H
#define COMPUTERGRAPHICS_RAY_H

#include "../maths/Vector.h"

class ray {
private:
    Vector origin;
    Vector direction;
public:
    ray();
    ray(const Vector &origin, const Vector &direction);
    ray rayFromPoints(const Vector &origin, const Vector &end) const;

    // Setter and getter
    const Vector &getOrigin() const;
    void setOrigin(const Vector &origin);
    const Vector &getDirection() const;
    void setDirection(const Vector &direction);

    Vector operator*(const float t) const;

    friend std::ostream &operator<<(std::ostream &os, const ray &r);
};


#endif //COMPUTERGRAPHICS_RAY_H
