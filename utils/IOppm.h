/*
 * Class for manipulating the input and output of image files ppm
 */

#ifndef COMPUTERGRAPHICS_IOPPM_H
#define COMPUTERGRAPHICS_IOPPM_H

#include <iostream>
using namespace std;

class IOppm {
public:
    static void read(const string &path);       // Read from a file in path the ppm image
    static void store(const string &path);      // Store the ppm image in the path

};


#endif //COMPUTERGRAPHICS_IOPPM_H
