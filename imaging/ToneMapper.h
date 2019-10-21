//
// Created by ccucr on 21/10/2019.
//

#ifndef TONEMAPPER_H
#define TONEMAPPER_H


#include "Image.h"

class ToneMapper {
public:
    static void clamping(Image &image, float clampValue);
    static void equalization(Image &image);
    static void equalAndClamp(Image &image, float clampValue);
    static void gamma(Image &image, float gamma);
    static void clampAndGamma(Image &image, float clampValue, float gamma);
};


#endif //TONEMAPPER_H
