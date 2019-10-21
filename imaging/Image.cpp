//
// Created by ccucr on 21/10/2019.
//

#include "Image.h"

Image::Image(const string &name, float maxValue, int width, int height, int colorDepth) : name(name),
                                                                                          maxValue(maxValue),
                                                                                          width(width), height(height),
                                                                                          colorDepth(colorDepth) {
    pixels.resize(width*height);
}

Image::~Image() {

}

void Image::setName(const string &name) {
    this->name = name;
}

void Image::setMaxValue(float maxValue) {
    this->maxValue = maxValue;
}

void Image::setWidth(int width) {
    this->width = width;
}

void Image::setHeight(int height) {
    this->height = height;
}

void Image::setColorDepth(int colorDepth) {
    this->colorDepth = colorDepth;
}

void Image::setPixel(int pos, const RGB &rgb) {
    this->pixels[pos] = rgb;
}

void Image::setPixel(int row, int col, const RGB &rgb) {
    this->pixels[row*width + col] = rgb;
}

const string &Image::getName() const {
    return name;
}

float Image::getMaxValue() const {
    return maxValue;
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

int Image::getColorDepth() const {
    return colorDepth;
}

const vector<RGB> &Image::getPixels() const {
    return pixels;
}
