//
// Created by Sergio on 12/11/2019.
//

#include <Matrix.h>
#include "TriangleMeshes.h"

TriangleMeshes::TriangleMeshes(const string &obj_path) {
    ifstream stream;
    stream.open(obj_path);

    string line;
    float x, y, z;  // For vertex or normal
    string s_x, s_y, s_z; // For faces
    if(stream.is_open()){
        while(getline(stream, line)){
            if(line.front() == '#'){
                // Its a comentary
            }else if(line.front() == 'v'){
                // Its geometric vertex or normal vertex
                if(line.at(1) == 'n'){
                    // Normal vertex
                    line.erase(0, 3);
                    stringstream stream_line(line);
                    stream_line >> x >> y >> z;
                    vertex_normal.emplace_back(x, y, z, 0);
                }else{
                    // Geometric vertex
                    line.erase(0,2);    // Clean the 'v'
                    stringstream stream_line(line);
                    stream_line >> x >> y >> z;
                    geometric_vertex.emplace_back(x, y, z, 1);
                }
            }else if(line.front() == 'f'){
                // Faces
                line.erase(0,2);    // Clean the 'f'
                stringstream stream_line(line);
                stream_line >> s_x >> s_y >> s_z;
                Vector a = geometric_vertex.at(s_x.front() - '0' - 1);
                Vector a_normal = vertex_normal.at(s_x.back() - '0' - 1);
                Vector b = geometric_vertex.at(s_y.front() - '0' - 1);
                Vector c = geometric_vertex.at(s_z.front() - '0' - 1);
                Triangle triangle(a,b,c); triangle.set_normal(a_normal);
            }
        }

    }else{
        cerr<<" The obj cant opened"<<endl;
        exit(1);
    }
}

bool TriangleMeshes::intersection(const Ray &ray, float &t) {
    return false;
}

Vector TriangleMeshes::get_normal(const Vector &collision_point) const {
    return Vector();
}

RGB TriangleMeshes::getEmision() {
    return RGB();
}
