//
// Created by ccucr on 21/10/2019.
//

#include "ToneMapper.h"

void ToneMapper::clamping(Image &image, float clampValue) {
    RGB rgb = RGB();
    for(int i = 0; i < image.getPixels().size(); i++){
        // Set the pixel
        rgb.set(RED,image.getPixels()[i].get(RED) < image.getColorDepth() * clampValue ? image.getPixels()[i].get(RED) : clampValue);

        rgb.set(GREEN,image.getPixels()[i].get(GREEN) < image.getColorDepth() * clampValue ? image.getPixels()[i].get(GREEN) : clampValue);

        rgb.set(BLUE,image.getPixels()[i].get(BLUE) < image.getColorDepth() * clampValue ? image.getPixels()[i].get(BLUE) : clampValue);

        image.setPixel(i, rgb);
    }
}
