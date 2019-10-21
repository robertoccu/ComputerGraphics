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

std::ostream &operator<<(std::ostream &os, const RGB &rgb) {
    os << std::fixed;
    os << std::setprecision(2);     // Number of decimals

    os << std::setw(7)<<"R: "<<rgb.get(RED)<<std::endl;
    os << std::setw(7)<<"G: "<<rgb.get(GREEN)<<std::endl;
    os << std::setw(7)<<"B: "<<rgb.get(BLUE)<<std::endl;

    return os;
}
