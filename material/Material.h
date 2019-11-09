//
// Created by Sergio on 08/11/2019.
//

#ifndef COMPUTERGRAPHICS_MATERIAL_H
#define COMPUTERGRAPHICS_MATERIAL_H

#include "../imaging/RGB.h"

class Material{
    virtual RGB get_emision() = 0;
};

#endif //COMPUTERGRAPHICS_MATERIAL_H
