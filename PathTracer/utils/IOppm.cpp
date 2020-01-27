#include <fstream>
#include "IOppm.h"

/**
 * Read a ppm file from path and return a image class
 * @param path The path of the ppm file
 */
Image IOppm::read(const string &path) {
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
    int width, height, colorDepth;
    float maxValue;

    // Read the type of the file
    getline(inputFile, type);

    // Read the max value floating
    string sMaxValue;
    getline(inputFile, sMaxValue);
    maxValue = stof(sMaxValue.substr(sMaxValue.find('=')+1));

    // Read the name
    getline(inputFile, name);

    // Read the width
    string sWidth;
    getline(inputFile, sWidth, ' ');
    width = stoi(sWidth, nullptr, 10);

    // Read the height
    string sHeight;
    getline(inputFile, sHeight);
    height = stoi(sHeight, nullptr, 10);

    // Read the resolution of color
    string sColorRes;
    getline(inputFile, sColorRes);
    colorDepth = stoi(sColorRes, nullptr, 10);

    // We create the image with the attributes obtained from the file
    Image image(name, maxValue, width, height, colorDepth);
    string red, green, blue;
    float realRed, realGreen, realBlue;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            // Obtain the red value
            inputFile >> red;
            realRed = stoi(red, nullptr, 10) * maxValue / colorDepth;

            // Obtain the green value
            inputFile >> green;
            realGreen = stoi(green, nullptr, 10) * maxValue / colorDepth;

            // Obtain the blue value
            inputFile >> blue;
            realBlue = stoi(blue, nullptr, 10) * maxValue / colorDepth;

            // Set the pixel in the image with the 3 values
            image.setPixel(i, j, RGB(realRed, realGreen, realBlue));
        }
    }

    // Set the color resolution now to max_value
    image.setColorDepth(maxValue);

    // Return the image
    return image;

}


void IOppm::store(const string &path, const Image &image, const int colorDepth) {
    ofstream outputFile;
    outputFile.open(path);
    if(outputFile.is_open()){
        outputFile << "P3"<<endl;
        outputFile << "#MAX=" <<image.getMaxValue()<<endl;
        outputFile << "# "<< image.getName()<<endl;
        outputFile << image.getWidth() <<" "<<image.getHeight()<<endl;
        outputFile << colorDepth <<endl;

        // Iterate for all the pixels
        long lRed, lGreen, lBlue;
        for(int i = 0; i < image.getPixels().size(); i++){
            // End of line because column is finish
            if(i != 0 && (i % image.getWidth()) == 0){
                outputFile<<endl;
            }

            // Set the pixel
            lRed = image.getPixels()[i].get(RED) * colorDepth / image.getMaxValue();

            lGreen = image.getPixels()[i].get(GREEN) * colorDepth / image.getMaxValue();

            lBlue = image.getPixels()[i].get(BLUE) * colorDepth / image.getMaxValue();

            outputFile << lRed << " " << lGreen << " " << lBlue << "     ";
        }
    }
}
