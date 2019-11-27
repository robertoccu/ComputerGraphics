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
public:
    DotLight(const Vector& pos, const RGB& light) : position(pos), color(light){}

    const Vector &getPosition() const;

    RGB light_in_the_point(const Vector& point) const;
};


#endif //COMPUTERGRAPHICS_DOTLIGHT_H
