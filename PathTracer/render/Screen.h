
#ifndef COMPUTERGRAPHICS_SCREEN_H
#define COMPUTERGRAPHICS_SCREEN_H

#include <vector>
#include <random>
#include "../maths/Vector.h"
#include "../maths/Matrix.h"
#include "Camera.h"

/**
 * The class Screen represents the display on which the rays are launched to collide with objects.
 * It stores the number of pixels per column and the number of pixels per row, i.e. the resolution of the image.
 * Stores the coordinates of the upper left corner of each pixel in world coordinates.
 */
class Screen {
private:
    float width, height, focal_length;
    int pixels_column, pixels_row;

    /*
     * Specifies how much you can move in both X and Y directions a point in the upper left corner
     * before reaching another pixel in world coordinates.
     * It can also be seen as the size of a pixel in world coordinates.
     */
    float size_X, size_Y;

    // Coordinates of the position of the upper left corner of each pixel in world coordinates
    std::vector<Vector> pixels_world_coordinates;
private:
    Screen(float width, float height, float focal_length,  int pixels_column,  int pixels_row);
    void calculate_world_coordinates(const Camera& camera);
    void set_world_coordinates( int row,  int column, const Vector& vector);
    Vector get_world_coordinates( int row,  int column) const;

public:
    Screen( int pixels_column,  int pixels_row, const Camera& camera);
    Screen();

    Vector get_pixel( int pixel_row,  int pixel_column) const;

     int getPixelsColumn() const;
     int getPixelsRow() const;


};


#endif //COMPUTERGRAPHICS_SCREEN_H
