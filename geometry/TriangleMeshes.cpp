//
// Created by Sergio on 12/11/2019.
//

/*#include <Matrix.h>
#include <cmath>
#include <random>
#include "TriangleMeshes.h"
#include "../utils/Prng.h"
#include "../material/Emitter.h"

/**
 * Load a triangle mesh of the obj file. At the same, move scale and rotate the points.
 * @param obj_path Obj with vertex, vertex normal, and faces style f 1//3 3//4 5//5. Dont have uv coordinates,
 *                  or any reference to any material.
 * @param matrix Matrix to change base
 *//*
list<Triangle> TriangleMeshes::get_triangles_without_textures(const string &obj_path, const Matrix &matrix) {
    std::vector<Vector> geometric_vertex;
    std::vector<Vector> vertex_normal;
    list<Triangle> triangles;

    ifstream stream;
    stream.open(obj_path);

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
                float red   = Prng::random();
                float green = Prng::random();
                float blue  = Prng::random();
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

/**
 * Load a triangle mesh of the obj file. At the same, move scale and rotate the points. Asign the materials of the mtl file
 * @param obj_path Obj with vertex, vertex normal, and faces style f 1//3 3//4 5//5. Dont have uv coordinates but contains
 *                  references to materials
 * @param mtl_path mtl file with simple materials and without texture mapping
 * @param matrix matrix to change base
 * @return
 *//*
list<Triangle> TriangleMeshes::get_triangles_with_textures_simple(const string &obj_path, const string &mtl_path,
                                                                  const Matrix &matrix) {
    std::map<string, Composite> materials = get_material_mtl(mtl_path);
    std::vector<Vector> geometric_vertex;
    std::vector<Vector> vertex_normal;
    list<Triangle> triangles;

    ifstream stream;
    stream.open(obj_path);

    string line;
    float x, y, z;  // For vertex or normal
    string s_x, s_y, s_z; // For faces
    int front, back; // For faces too
    Vector face_normal;

    ssize_t finder_pointer;
    Composite composite_material;

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
            }else if((finder_pointer = line.find("usemtl") != string::npos)){
                // Set new composite material
                composite_material = Composite(materials.at(line.substr(finder_pointer + 6, line.length())));
            }
            else if(line.front() == 'f'){
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
                // TODO: Now only save emitter materials, latter all
                shared_ptr<Emitter> emitter = make_shared<Emitter>(composite_material.get_emision());
                triangle.set_material(emitter);
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

/**
 * Returns the simple materials contained in the mtl file.
 * Return complete material (Ke, Kd, Ks)
 * @param mtl_path mtl file without mapping textures, only with Phong materials.
 * @return map<material_string, material>
 *//*
std::map<string, Composite> TriangleMeshes::get_material_mtl(const string &mtl_path) {
    std::map<string, Composite> materials{};

    ifstream stream;
    stream.open(mtl_path);
    string line;
    size_t finder_pointer;
    RGB Kd, Ks, Ke;
    float Ns = 0;

    if(stream.is_open()){
        while(getline(stream, line)){
            if(line.front() == '#'){
                // Comentary
            }else if((finder_pointer = line.find("newmtl") != string::npos)){
                // New material
                string name_material = line.substr(finder_pointer + 6, line.length());  // Obtain the name_material
                for(int i = 0; i < 8; i++){
                    // Obtain new line
                    getline(stream, line);
                    // Find if is Kd, Ks..etc
                    if(line[0] == 'K' && line[1] == 'd'){
                        // Diffuse coefficient
                        line.replace(0,2,"");   // Erase Kd
                        float red, green, blue;
                        stringstream ss(line);
                        ss >> red; ss >> green; ss >> blue;
                        Kd = RGB(red, green, blue);
                    }else if(line[0] == 'K' && line[1] == 's'){
                        // Specular coefficient
                        line.replace(0,2,"");   // Erase Ks
                        float red, green, blue;
                        stringstream ss(line);
                        ss >> red; ss >> green; ss >> blue;
                        Ks = RGB(red, green, blue);
                    }else if(line[0] == 'K' && line[1] == 'e'){
                        // Emision
                        line.replace(0,2,"");   // Erase Ke
                        float red, green, blue;
                        stringstream ss(line);
                        ss >> red; ss >> green; ss >> blue;
                        Ke = RGB(red, green, blue);
                    }else if(line[0] == 'N' && line[1] == 's'){
                        // Shininess
                        line.replace(0,2,"");   // Erase Ns
                        Ns = stof(line);
                    }
                }

                // Update the map
                materials.emplace(name_material, Composite(Emitter(Ke), Phong(Kd,Ks, Ns)));

            }
        }
    }else{
        cerr<<" The mtl cant opened"<<endl;
        exit(1);
    }

    return materials;

}
*/