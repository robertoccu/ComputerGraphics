//
// Created by Sergio on 12/11/2019.
//

#include <Matrix.h>
#include <cmath>
#include <random>
#include "TriangleMeshes.h"

/**
 * Load a triangle mesh of the obj file. At the same, move scale and rotate the points.
 * @param obj_path Obj with vertex, vertex normal, and faces style f 1//2 3//2 5//2. With the same last character.
 * @param matrix Matrix to change base
 */
list<Triangle> TriangleMeshes::obtain_triangles(const string &obj_path, const Matrix &matrix) {
    std::vector<Vector> geometric_vertex;
    std::vector<Vector> vertex_normal;
    list<Triangle> triangles;

    ifstream stream;
    stream.open(obj_path);
    // DEBUG
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    string line;
    float x, y, z;  // For vertex or normal
    string s_x, s_y, s_z; // For faces
    int front, back; // For faces too
    Vector face_normal;

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
                string delimiter = "//";

                front = stoi(s_x.substr(0, s_x.find(delimiter)));
                Vector a = geometric_vertex.at(front - 1); a = matrix * a;
                back  = stoi(s_x.substr(s_x.find(delimiter)+2, s_x.length()));
                Vector a_normal = vertex_normal.at(back - 1); a_normal = (matrix * a_normal).normalize();

                front = stoi(s_y.substr(0, s_y.find(delimiter)));
                Vector b = geometric_vertex.at(front - 1); b = matrix * b;
                back  = stoi(s_y.substr(s_y.find(delimiter)+2, s_y.length()));
                Vector b_normal = vertex_normal.at(back - 1); b_normal = (matrix * b_normal).normalize();

                front = stoi(s_z.substr(0, s_z.find(delimiter)));
                Vector c = geometric_vertex.at(front - 1); c = matrix * c;
                back  = stoi(s_z.substr(s_z.find(delimiter)+2, s_z.length()));
                Vector c_normal = vertex_normal.at(back - 1); c_normal = (matrix * c_normal).normalize();

                face_normal = (a_normal + b_normal + c_normal) / 3;
                face_normal = face_normal.normalize();

                Triangle triangle(a,b,c); triangle.set_normal(face_normal);
                // DEBUG
                float red   = dist(mt);
                float green = dist(mt);
                float blue  = dist(mt);
                shared_ptr<Emitter> aleatorio = make_shared<Emitter>(RGB(red, green, blue));
                triangle.set_material(aleatorio);
                triangles.push_back(triangle);
            }
        }

    }else{
        cerr<<" The obj cant opened"<<endl;
        exit(1);
    }

    // When the triangles has saved, we can clean the other vectors
    geometric_vertex.clear();
    vertex_normal.clear();
    return triangles;
}
