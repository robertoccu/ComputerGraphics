//
// Created by Sergio on 26/11/2019.
//

#ifndef COMPUTERGRAPHICS_DOTLIGHT_H
#define COMPUTERGRAPHICS_DOTLIGHT_H


#include <Vector.h>
#include "RGB.h"

class DotLight {
private:
    Vector position;
    RGB color;
    float power;
public:
    DotLight(const Vector& pos, const RGB& light, float power) : position(pos), color(light), power(power){}

    const Vector &getPosition() const;
    const float &getPower() const { return power;}

    RGB light_in_the_point(const Vector& point) const;
};


#endif //COMPUTERGRAPHICS_DOTLIGHT_H
