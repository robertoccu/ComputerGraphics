//
// Created by Sergio on 12/11/2019.
//

#ifndef COMPUTERGRAPHICS_TRIANGLEMESHES_H
#define COMPUTERGRAPHICS_TRIANGLEMESHES_H

#include <fstream>
#include <vector>
#include "CollisionObject.h"
#include "Triangle.h"


class TriangleMeshes : public CollisionObject{
private:
    std::vector<Vector> geometric_vertex;
    std::vector<Vector> vertex_normal;
    std::vector<Vector> space_vertex;

    list<Triangle> triangles;
    RGB emision;

public:
    TriangleMeshes(const string &obj_path, const Matrix &matrix);

    bool intersection(const Ray &ray, float &t) override;

    Vector get_normal(const Vector &collision_point) const ;



};


#endif //COMPUTERGRAPHICS_TRIANGLEMESHES_H
