/**
 * RGB
 */

#ifndef RGB_H
#define RGB_H

#include <iostream>
#include <list>
#include <iomanip>

#define RED 0
#define GREEN 1
#define BLUE 2

using namespace std;

class RGB {
private:
    float value[3];
public:
    RGB();
    RGB(float red, float green, float blue);

    ~RGB();

    /* Get & Set */
    float get(int color) const;
    void set(int color, float value);
    void set(float red, float green, float blue);

    /* Operator overload */
    RGB operator+(const RGB &rgb) const;
    RGB operator+=(const RGB &rgb);

    /* Screen output */
    friend std::ostream &operator<<(std::ostream &os, const RGB &rgb);
};

#endif //RGB_H