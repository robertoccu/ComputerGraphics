//
// Created by ccucr on 21/10/2019.
//

#include "RGB.h"



RGB::RGB() {
    this->value[RED] = 0;
    this->value[GREEN] = 0;
    this->value[BLUE] = 0;
}

RGB::RGB(float red, float green, float blue) {
    this->value[RED] = red;
    this->value[GREEN] = green;
    this->value[BLUE] = blue;
}

RGB::~RGB() = default;

float RGB::get(int color) const {
    return this->value[color];
}

void RGB::set(int color, float value) {
    this->value[color] = value;
}

void RGB::set(float red, float green, float blue) {
    this->value[RED] = red;
    this->value[GREEN] = green;
    this->value[BLUE] = blue;
}

RGB RGB::operator+(const RGB &rgb) const {
    return RGB(this->get(RED) + rgb.get(RED), this->get(GREEN) + rgb.get(GREEN),
            this->get(BLUE) + rgb.get(BLUE));
}

RGB RGB::operator+=(const RGB &rgb) {
    this->set(this->get(RED) + rgb.get(RED), this->get(GREEN) + rgb.get(GREEN),
              this->get(BLUE) + rgb.get(BLUE));
    return *this;
}

/**
 * Converts RGB color space to xyY space, where Y is the illuminance
 * @return A tuple<x, y, Y>
 */
tuple<float, float, float> RGB::RGBtoxyY () const{
    float R = this->get(RED);
    float G = this->get(GREEN);
    float B = this->get(BLUE);

    // Convert from RGB to XYZ
    float X = R * 0.4124 + G * 0.3576 + B * 0.1805;
    float Y = R * 0.2126 + G * 0.7152 + B * 0.0722;
    float Z = R * 0.0193 + G * 0.1192 + B * 0.9505;

    // Convert XYZ to xyY
    float L = (X + Y + Z);
    return make_tuple(X/L, Y/L, Y);
}

/**
 * Converts xyY color space to RGB space, where Y is the illuminance
 * @param xyY tuple<x, y, Y> in xyY colour space
 * @return rgb
 */
RGB RGB::xyYtoRGB(const tuple<float, float, float> &xyY) const{
    // Convert from xyY to XYZ
    float x = std::get<0>(xyY);
    float y = std::get<1>(xyY);
    float Y = std::get<2>(xyY);

    float X = x * (Y / y);
    float Z = (1 - x - y) * (Y / y);

    RGB rgb = RGB();
    // Convert from XYZ to RGB
    rgb.set(RED, X *  3.2406 + Y * -1.5372 + Z * -0.4986);
    rgb.set(GREEN, X * -0.9689 + Y *  1.8758 + Z *  0.0415);
    rgb.set(BLUE, X *  0.0557 + Y * -0.2040 + Z *  1.0570);

    return rgb;
}

std::ostream &operator<<(std::ostream &os, const RGB &rgb) {
    os << std::fixed;
    os << std::setprecision(2);     // Number of decimals

    os << std::setw(7)<<"R: "<<rgb.get(RED)<<std::endl;
    os << std::setw(7)<<"G: "<<rgb.get(GREEN)<<std::endl;
    os << std::setw(7)<<"B: "<<rgb.get(BLUE)<<std::endl;

    return os;
}
