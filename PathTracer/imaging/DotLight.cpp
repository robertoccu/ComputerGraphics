//
// Created by Sergio on 26/11/2019.
//

#include <cmath>
#include "DotLight.h"

/**
 * Returns the light that comes to a point in the space
 * @param point
 * @return
 */
RGB DotLight::light_in_the_point(const Vector &point) const {
    // Obtain the distance from the center and the point
    float distance = (this->position - point).modulus();
    // The square distance
    distance = pow(distance, 2);
    // The light is the color divided by the distance square
    return (color * power) / distance;
}

const Vector &DotLight::getPosition() const {
    return position;
}
