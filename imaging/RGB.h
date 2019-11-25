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

    static RGB red;
    static RGB green;
    static RGB blue;
    static RGB yellow;
    static RGB magenta;
    static RGB cyan;
    static RGB white;
    static RGB black;

    RGB();
    RGB(float red, float green, float blue);

    ~RGB();

    /* Get & Set */
    float get(int color) const;
    void set(int color, float value);
    void set(float red, float green, float blue);

    /* Operator overload */
    RGB operator+(const RGB &rgb) const;
    RGB operator*(float f) const;
    friend RGB operator*(float f, const RGB& rgb) ;
    RGB operator+=(const RGB &rgb);

    tuple<float, float, float> RGBtoxyY () const;
    RGB xyYtoRGB(const tuple<float, float, float> &xyy) const;

    float get_mean_color() const{
       return (this->get(0) + this->get(1) + this->get(2)) / 3;
    }


    static RGB average_colors(const RGB *colors, int size);

    /* Screen output */
    friend std::ostream &operator<<(std::ostream &os, const RGB &rgb);
};

#endif //RGB_H