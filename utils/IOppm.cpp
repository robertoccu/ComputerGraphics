//
// Created by Sergio on 17/10/2019.
//

#include <fstream>
#include "IOppm.h"

/**
 * Default constructor
 */
IOppm::IOppm() {}

/**
 * Default destructor
 */
IOppm::~IOppm() {}

/**
 * Read a ppm file from path and save their atributtes
 * @param path The path of the ppm file
 */
void IOppm::read(const string &path) {
    ifstream inputFile;
    inputFile.open(path);
    if(!inputFile.is_open()){
        cout<<"ERROR: The file could not be opened"<<endl;
        exit(EXIT_FAILURE);
    }
    // The file could be opened

    // For simplicity of the code,
    // let's assume that the file is syntactically correct

    // Variables to store the image atributtes
    string type, name;
    int width, height, color_resolution;
    float max_value;

    // Read the type of the file
    getline(inputFile, type);

    // Read the max value floating
    string s_max_value;
    getline(inputFile, s_max_value);
    max_value = stoi(s_max_value.substr(s_max_value.find("=")+1), nullptr, 10);

    // Read the name
    getline(inputFile, name);

    // Read the width
    string s_width;
    getline(inputFile, s_width, ' ');
    width = stoi(s_width, nullptr, 10);

    // Read the height
    string s_height;
    getline(inputFile, s_height);
    height = stoi(s_height, nullptr, 10);

    // Read the resolution of color
    string s_color_res;
    getline(inputFile, s_color_res);
    color_resolution = stoi(s_color_res, nullptr, 10);

    // We create the image with the attributes obtained from the file
    // Image image();
    string red, green, blue;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            // Obtain the red value
            inputFile >> red;
            long l_red = stoi(red, nullptr, 10);

            // Obtain the green value
            inputFile >> green;
            long l_green = stoi(green, nullptr, 10);

            // Obtain the blue value
            inputFile >> blue;
            long l_blue = stoi(blue, nullptr, 10);

            // Set the pixel in the image with the 3 values
            //image.setPixel(i, j, RGB())
        }
    }

    // Set the color resolution now to max_value
    //image.setColorRes(max_value)

    // Return the image
    // return image;

}

void IOppm::store(const string &path) {

}
