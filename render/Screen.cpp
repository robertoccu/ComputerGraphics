//
// Created by Sergio on 08/11/2019.
//

#include "Screen.h"

Screen::Screen(float width, float height, float focal_length, unsigned int pixels_column, unsigned int pixels_row) : width(
        width), height(height), focal_length(focal_length), pixels_column(pixels_column), pixels_row(pixels_row) {

    /*
     * As the screen in camera coordinates measures 2 (-1 to 1),
     * if you divide the size by the number of pixels you get how much each pixel measures.
     */
    size_X = 2 / (float) pixels_column;
    size_Y = 2 / (float) pixels_row;
    pixels_world_coordinates.resize(pixels_column * pixels_row);

}

Screen::Screen(unsigned int pixels_column, unsigned int pixels_row, const Camera &camera) :
    Screen(camera.getLeft().modulus() * 2, camera.getUp().modulus() * 2, camera.getForward().modulus(),
           pixels_column, pixels_row) {
    calculate_world_coordinates(camera);
}

/**
 * Function that calculates the position of the upper left corner of each pixel in global coordinates and stores them in the vector.
 */
void Screen::calculate_world_coordinates(const Camera& camera) {
    // First we obtain the matrix of change of base of coordinates of the camera to coordinates of the world.
    Matrix transformation_matrix;
    transformation_matrix.setVectors(camera.getLeft(), camera.getForward(), camera.getUp());
    transformation_matrix.setPoint(camera.getPosition());

    for(unsigned int i = 0; i < this->pixels_row; i++){
        for(unsigned int j = 0; j < this->pixels_column; j++){
            // Since the camera has the vector left as X, 1.1 is the upper left corner.
            // Then we advance subtracting to 1 because pixel we are using the size of the pixel.
            // The Y axis is always 1 because it is in camera coordinates.
            Vector pixel(1 - (j * size_X), 1, 1 - (i * size_Y), 1);

            // Change the base of the camera to the world
            pixel = transformation_matrix * pixel;
            set_world_coordinates(i, j, pixel);
        }
    }
}


void Screen::set_world_coordinates(unsigned int row, unsigned int column, const Vector &vector) {
    pixels_world_coordinates[pixels_column * row + column] = vector;
}


Vector Screen::get_world_coordinates(unsigned int row, unsigned int column) const {
    return pixels_world_coordinates[pixels_column * row + column];
}

/**
 *
 * @param pixel_row
 * @param pixel_column
 * @return
 */
Vector Screen::get_pixel(unsigned int pixel_row, unsigned int pixel_column) const {
    /* We get the pixel size in world coordinates. Since all pixels measure the same,
     * we can use any pixel to calculate them.
     */
    float size_pixel_X = this->width  / (float) this->pixels_column;
    float size_pixel_Y = this->height / (float) this->pixels_row ;

    // Obtain the pixel in world coordinates
    Vector pixel = get_world_coordinates(pixel_row, pixel_column);

    // For the moment we always return the point of the center of the pixel.
    // TODO: Do it with a random number, not always in the middle. It is enough to multiply by a
    //  number between 0 and 1 the size of the pixel.
    pixel.set(0, pixel.get(0) + size_pixel_X/2);
    pixel.set(2, pixel.get(2) - size_pixel_Y/2);

    return pixel;
}
