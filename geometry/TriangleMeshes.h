//
// Created by Sergio on 12/11/2019.
//

#ifndef COMPUTERGRAPHICS_TRIANGLEMESHES_H
#define COMPUTERGRAPHICS_TRIANGLEMESHES_H

#include <fstream>
#include <vector>
#include <map>
#include "Triangle.h"


class TriangleMeshes{
public:
    static list<Triangle> get_triangles_without_textures(const string &obj_path, const Matrix &matrix);
    static list<Triangle> get_triangles_with_textures_simple(const string &obj_path, const string &mtl_path, const Matrix &matrix);
    // TODO: static list<Triangle> get_triangles_with_textures_uv(const string &obj_path, const string &mtl_path, const Matrix &matrix);
private:
    static std::map<string, RGB> get_material_mtl(const string &mtl_path);
    // TODO: method to parse the mtl file and get the texture mapping.
};


#endif //COMPUTERGRAPHICS_TRIANGLEMESHES_H
