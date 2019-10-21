//
// Created by ccucr on 21/10/2019.
//

#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>
#include "RGB.h"

class Image {
private:
    std::string name;
    float maxValue;
    int width, height;
    int colorDepth;
    std::vector<RGB> pixels;

public:
    const string &getName() const;

    float getMaxValue() const;

    int getWidth() const;

    int getHeight() const;

    int getColorDepth() const;

    const vector<RGB> &getPixels() const;

    ~Image();

    Image(const string &name, float maxValue, int width, int height, int colorDepth);

    void setName(const string &name);

    void setMaxValue(float maxValue);

    void setWidth(int width);

    void setHeight(int height);

    void setColorDepth(int colorDepth);

    void setPixel(int pos, const RGB &rgb);

    void setPixel(int row, int col, const RGB &rgb);

};


#endif //IMAGE_H
