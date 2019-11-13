//
// Created by Sergio on 12/11/2019.
//

#ifndef COMPUTERGRAPHICS_TRIANGLEMESHES_H
#define COMPUTERGRAPHICS_TRIANGLEMESHES_H

#include <fstream>
#include <vector>
#include "Triangle.h"


class TriangleMeshes{
public:
    static list<Triangle> obtain_triangles(const string &obj_path, const Matrix &matrix);
};


#endif //COMPUTERGRAPHICS_TRIANGLEMESHES_H
