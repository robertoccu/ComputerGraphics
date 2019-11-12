//
// Created by Sergio on 12/11/2019.
//

#ifndef COMPUTERGRAPHICS_EMITTER_H
#define COMPUTERGRAPHICS_EMITTER_H


#include "Material.h"

class Emitter : public Material{
    RGB color_emitter;
public:
    Emitter(const RGB &color);
    RGB get_emision() override;
};


#endif //COMPUTERGRAPHICS_EMITTER_H
