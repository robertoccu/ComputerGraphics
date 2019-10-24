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
    image.setMaxValue(clampValue);
}

void ToneMapper::equalization(Image &image) {
    RGB rgb = RGB();
    for(int i = 0; i < image.getPixels().size(); i++){
        // Set the pixel
        rgb.set(RED,image.getPixels()[i].get(RED) / image.getMaxValue());

        rgb.set(GREEN,image.getPixels()[i].get(GREEN) / image.getMaxValue());

        rgb.set(BLUE,image.getPixels()[i].get(BLUE) / image.getMaxValue());

        image.setPixel(i, rgb);
    }
    image.setMaxValue(1);
}

void ToneMapper::equalAndClamp(Image &image, float clampValue) {
    ToneMapper::clamping(image,clampValue);
    ToneMapper::equalization(image);
    image.setMaxValue(1);
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
    image.setMaxValue(1);

}

void ToneMapper::clampAndGamma(Image &image, float clampValue, float gamma) {
    ToneMapper::clamping(image, clampValue);
    ToneMapper::gamma(image, gamma);
}

void RGBtoxyY(RGB rgb, float &x, float &y, float &Y) {
    float R = rgb.get(RED);
    float G = rgb.get(GREEN);
    float B = rgb.get(BLUE);

    // Convert from RGB to XYZ
    float X = R * 0.4124 + G * 0.3576 + B * 0.1805;
    Y = R * 0.2126 + G * 0.7152 + B * 0.0722;
    float Z = R * 0.0193 + G * 0.1192 + B * 0.9505;

    // Convert from XYZ to xyY
    float L = (X + Y + Z);
    x = X / L;
    y = Y / L;
}

void xyYtoRGB(float x, float y, float Y,
              RGB &rgb)
{
    // Convert from xyY to XYZ
    float X = x * (Y / y);
    float Z = (1 - x - y) * (Y / y);

    rgb = RGB();
    // Convert from XYZ to RGB
    rgb.set(RED, X *  3.2406 + Y * -1.5372 + Z * -0.4986);
    rgb.set(GREEN, X * -0.9689 + Y *  1.8758 + Z *  0.0415);
    rgb.set(BLUE, X *  0.0557 + Y * -0.2040 + Z *  1.0570);
}

void ToneMapper::reinhard(Image &image, RGB Lwhite_rgb) {

    float x, y, Y, L, Lwhite;
    RGB output = RGB();
    RGBtoxyY(Lwhite_rgb, x, y, Lwhite);
    for(int i = 0; i < image.getPixels().size(); i++){
        RGBtoxyY(image.getPixels()[i], x, y, Y);

        L = Y;
        float Lxy = (L * (1 + (L / pow(Lwhite,2))))/(1+L);

        xyYtoRGB(x, y, Lxy, output);

        image.setPixel(i, output);
    }
}