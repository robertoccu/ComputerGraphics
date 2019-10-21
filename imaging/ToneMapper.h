//
// Created by ccucr on 21/10/2019.
//

#ifndef TONEMAPPER_H
#define TONEMAPPER_H


#include "Image.h"

class ToneMapper {
public:
    static void clamping(Image &image, float clampValue);
};


#endif //TONEMAPPER_H
