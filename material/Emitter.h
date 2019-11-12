//
// Created by Sergio on 12/11/2019.
//

#ifndef COMPUTERGRAPHICS_EMITTER_H
#define COMPUTERGRAPHICS_EMITTER_H

#include "Material.h"
#include "../imaging/RGB.h"

class Emitter : public Material{
    RGB emitter_color;
public:
    Emitter(const RGB &rgb){emitter_color = rgb;}
    RGB get_emision(){return emitter_color;}
};

#endif //COMPUTERGRAPHICS_EMITTER_H
