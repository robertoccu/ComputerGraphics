/**
 * RGB
 */

#ifndef RGB_H
#define RGB_H

#include <iostream>
#include <list>

using namespace std;

class RGB {
private:
    double value[3];
public:
    RGB();
    RGB(double red, double green, double blue);

    ~RGB();

    /* Operations */
    static RGB average(const std::list<RGB> &rgb);

    /* Operator overload */
    RGB operator+(const RGB &rgb) const;
    RGB operator+=(const RGB &rgb);

    /* Screen output */
    friend std::ostream &operator<<(std::ostream &os, const RGB &rgb);
};

#endif //RGB_H