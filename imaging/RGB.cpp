//
// Created by ccucr on 21/10/2019.
//

#include <cmath>
#include <Matrix.h>
#include "RGB.h"

RGB RGB::red = RGB(0.95,0.05,0.05);
RGB RGB::green = RGB(0.05,0.95,0.05);
RGB RGB::blue = RGB(0.05,0.05,0.95);
RGB RGB::yellow = RGB(0.95, 0.95, 0.05);
RGB RGB::magenta = RGB(0.95, 0.05, 0.95);
RGB RGB::cyan = RGB(0.05, 0.95, 0.95);
RGB RGB::white = RGB (0.95, 0.95, 0.95);
RGB RGB::black = RGB(0.05, 0.05, 0.05);


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

    //  Inverse Gamma Companding
    float gamma = 2.2; // For sRGB
    R = pow(R, gamma);
    G = pow(G, gamma);
    B = pow(B, gamma);

    // Linear RGB to XYZ
    Matrix WideGamutRGB_to_XYZ = Matrix();
    WideGamutRGB_to_XYZ.setVector(Vector(0.7161046, 0.2581874, 0.0, 0), 0);
    WideGamutRGB_to_XYZ.setVector(Vector(0.1009296, 0.7249378, 0.0517813, 0), 1);
    WideGamutRGB_to_XYZ.setVector(Vector(0.1471858, 0.0168748, 0.7734287, 0), 2);

    Matrix sRGB_to_XYZ = Matrix();
    sRGB_to_XYZ.setVector(Vector(0.4360747, 0.2225045, 0.0139322, 0), 0);
    sRGB_to_XYZ.setVector(Vector(0.3850649, 0.7168786, 0.0971045, 0), 1);
    sRGB_to_XYZ.setVector(Vector(0.1430804, 0.0606169, 0.7141733, 0), 2);

    // Select RGB Space Color
    Matrix RGB_to_XYZ = sRGB_to_XYZ;

    Vector RGB_vector(R, G, B, 0);

    Vector XYZ = RGB_to_XYZ * RGB_vector;

    float L = XYZ.get(0) + XYZ.get(1) + XYZ.get(2);
    return make_tuple(XYZ.get(0)/L, XYZ.get(1)/L, XYZ.get(1));
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

    float X = (x * Y) / y;
    float Z = ((1 - x - y) * Y) / y;

    // XYZ to Linear RGB
    Matrix XYZ_to_WideGamutRGB = Matrix();
    XYZ_to_WideGamutRGB.setVector(Vector(1.4628067, -0.5217933, 0.0349342, 0), 0);
    XYZ_to_WideGamutRGB.setVector(Vector(-0.1840623, 1.4472381, -0.0968930, 0), 1);
    XYZ_to_WideGamutRGB.setVector(Vector(-0.2743606, 0.0677227, 1.2884099, 0), 2);

    Matrix XYZ_to_sRGB = Matrix();
    XYZ_to_sRGB.setVector(Vector(3.1338561, -0.9787684, 0.0719453, 0), 0);
    XYZ_to_sRGB.setVector(Vector(-1.6168667, 1.9161415, -0.2289914, 0), 1);
    XYZ_to_sRGB.setVector(Vector(-0.4906146, 0.0334540, 1.4052427, 0), 2);

    // Select RGB Space Color
    Matrix XYZ_to_RGB = XYZ_to_sRGB;

    Vector XYZ_Vector(X, Y, Z, 0);

    Vector RGB_vector = XYZ_to_RGB * XYZ_Vector;

    // Gamma Companding
    float gamma = 2.2;
    float red,green,blue;
    if (RGB_vector.get(0) < 0) {
        red = 0;
    } else {
        red = pow(RGB_vector.get(0),(1/gamma));
    }
    if (RGB_vector.get(1) < 0) {
        green = 0;
    } else {
        green = pow(RGB_vector.get(1),(1/gamma));
    }
    if (RGB_vector.get(2) < 0) {
        blue = 0;
    } else {
        blue = pow(RGB_vector.get(2),(1/gamma));
    }

    return RGB(red, green, blue);
}

std::ostream &operator<<(std::ostream &os, const RGB &rgb) {
    os << std::fixed;
    os << std::setprecision(2);     // Number of decimals

    os << std::setw(7)<<"R: "<<rgb.get(RED)<<std::endl;
    os << std::setw(7)<<"G: "<<rgb.get(GREEN)<<std::endl;
    os << std::setw(7)<<"B: "<<rgb.get(BLUE)<<std::endl;

    return os;
}

RGB RGB::average_colors(const RGB *colors, int size) {
    float red = 0, green = 0, blue = 0;
    for(int i = 0; i < size; i++){
        red   += colors[i].get(RED);
        green += colors[i].get(GREEN);
        blue  += colors[i].get(BLUE);
    }
    return RGB(red/(float)size, green/(float)size, blue/(float)size);
}

RGB RGB::operator*(float f) const {
    return RGB(this->get(0) * f, this->get(1) * f, this->get(2) * f);
}

RGB operator*(float f, const RGB &rgb) {
    return rgb * f;
}
