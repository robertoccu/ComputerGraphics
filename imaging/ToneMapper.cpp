//
// Created by ccucr on 21/10/2019.
//

#include "ToneMapper.h"
#include <cmath>

void ToneMapper::clamping(Image &image, float clampValue) {
    RGB rgb = RGB();
    for(int i = 0; i < image.getPixels().size(); i++){
        // Set the pixel
        rgb.set(RED,image.getPixels()[i].get(RED) < clampValue ? image.getPixels()[i].get(RED) : clampValue);

        rgb.set(GREEN,image.getPixels()[i].get(GREEN) < clampValue ? image.getPixels()[i].get(GREEN) : clampValue);

        rgb.set(BLUE,image.getPixels()[i].get(BLUE) < clampValue ? image.getPixels()[i].get(BLUE) : clampValue);

        image.setPixel(i, rgb);
    }
}

void ToneMapper::equalization(Image &image) {
    RGB rgb = RGB();
    for(int i = 0; i < image.getPixels().size(); i++){
        // Set the pixel
        rgb.set(RED,image.getPixels()[i].get(RED) / image.getColorDepth());

        rgb.set(GREEN,image.getPixels()[i].get(GREEN) / image.getColorDepth());

        rgb.set(BLUE,image.getPixels()[i].get(BLUE) / image.getColorDepth());

        image.setPixel(i, rgb);
    }
}

void ToneMapper::equalAndClamp(Image &image, float clampValue) {
    ToneMapper::clamping(image,clampValue);
    ToneMapper::equalization(image);

}

void ToneMapper::gamma(Image &image, float gamma) {
    ToneMapper::equalization(image);

    RGB rgb = RGB();
    for(int i = 0; i < image.getPixels().size(); i++){
        // Set the pixel
        rgb.set(RED, pow(image.getPixels()[i].get(RED), gamma));

        rgb.set(GREEN,pow(image.getPixels()[i].get(GREEN), gamma));

        rgb.set(BLUE,pow(image.getPixels()[i].get(BLUE), gamma));

        image.setPixel(i, rgb);
    }

}

void ToneMapper::clampAndGamma(Image &image, float clampValue, float gamma) {
    ToneMapper::clamping(image, clampValue);
    ToneMapper::gamma(image, gamma);
}
