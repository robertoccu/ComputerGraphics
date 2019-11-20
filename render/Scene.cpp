//
// Created by Sergio on 08/11/2019.
//

#include <cmath>
#include <utility>
#include "Scene.h"
#include "../geometry/Sphere.h"
#include "../geometry/Plane.h"
#include "../geometry/Disk.h"
#include "../geometry/Triangle.h"
#include "../geometry/TriangleMeshes.h"

Scene::Scene(const std::list<CollisionObject*> &objectsList, const Camera &camera, const Screen &screen)
        : objects_list(objectsList), camera(camera), screen(screen) {}

Scene::Scene() = default;

/**
 *
 * @param ray
 * @param intersection_point
 * @return
 */
CollisionObject* Scene::near_intersection(const Ray &ray, Vector &intersection_point) const{
    float t_intersection = 0.0;
    float near_intersection = INFINITY;
    CollisionObject *collision_object = nullptr;

    // Iterate on the list of objects in the scene
    for(const auto& object : this->objects_list){
        //If the ray intersects with the object
        if(object->intersection(ray, t_intersection)){
            //If the point of intersection is less than the nearest point so far
            if(t_intersection < near_intersection){
                // The intersection point is updated
                near_intersection = t_intersection;
                collision_object = object;
            }
        }
    }
    // If he's at least collided with some object.
    if(near_intersection != INFINITY){
        // Obtain the intersection point
        intersection_point = Vector(ray.getOrigin() + (ray.getDirection() * t_intersection));
        return collision_object;
    }else{
        return nullptr;
    }
}

const Camera &Scene::getCamera() const {
    return camera;
}

const Screen &Scene::getScreen() const {
    return screen;
}

/**
 * Load the Cornell box scene.
 */
void Scene::load_cornellBox() {
    int resolution_X  = 16 * 54;
    int resolution_Y  = 16  * 54;
    int width_screen  = 16 *  4;
    int height_screen = 16  *  4;
    int focal_length  =  width_screen / (int)(2* tan(0.26 * M_PI)); // Fish Eye Avoidance Formula

    // Objects
    cout<<"Loading objects...";
    list<CollisionObject*> objects;

    // Debug X Axis
    static Sphere test0(Vector(5,0,0,PT),1);
    test0.set_material(make_shared<Emitter>(RGB::red));
    objects.push_back(&test0);

    static Sphere test1(Vector(10,0,0,PT),1);
    test1.set_material(make_shared<Emitter>(RGB::red));
    objects.push_back(&test1);

    static Sphere test2(Vector(20,0,0,PT),1);
    test2.set_material(make_shared<Emitter>(RGB::red));
    objects.push_back(&test2);

    // Debug Y Axis
    static Sphere test3(Vector(0,5,0,PT),1);
    test3.set_material(make_shared<Emitter>(RGB::green));
    objects.push_back(&test3);

    static Sphere test4(Vector(0,10,0,PT),1);
    test4.set_material(make_shared<Emitter>(RGB::green));
    objects.push_back(&test4);

    static Sphere test5(Vector(0,20,0,PT),1);
    test5.set_material(make_shared<Emitter>(RGB::green));
    objects.push_back(&test5);

    // Debug Z Axis
    static Sphere test6(Vector(0,0,5,PT),1);
    test6.set_material(make_shared<Emitter>(RGB::blue));
    objects.push_back(&test6);

    static Sphere test7(Vector(0,0,10,PT),1);
    test7.set_material(make_shared<Emitter>(RGB::blue));
    objects.push_back(&test7);

    static Sphere test8(Vector(0,0,20,PT),1);
    test8.set_material(make_shared<Emitter>(RGB::blue));
    objects.push_back(&test8);

    // Cornell Box with color values from implementation on Mitsuba renderer.
    static Plane left_wall(Vector(0,0,0,PT),Vector(1,0,0,VEC));
    left_wall.set_material(make_shared<Emitter>(RGB(0.570068, 0.0430135, 0.0443706)));
    objects.push_back(&left_wall);

    static Plane right_wall(Vector(30,0,0,PT),Vector(-1,0,0,VEC));
    right_wall.set_material(make_shared<Emitter>(RGB(0.105421, 0.37798, 0.076425)));
    objects.push_back(&right_wall);

    static Plane floor(Vector(0,0,0,PT),Vector(0,0,1,VEC));
    floor.set_material(make_shared<Emitter>(RGB(0.885809, 0.698859, 0.666422)));
    objects.push_back(&floor);

    static Plane ceil(Vector(0,0,30,PT),Vector(0,0,-1,VEC));
    ceil.set_material(make_shared<Emitter>(RGB(0.885809, 0.698859, 0.666422)));
    objects.push_back(&ceil);


    this->setObjectsList(objects);
    cout<<"Objects loaded successfully"<<endl;

    // Camera
    Camera camera_scene(Vector(15,-focal_length/1.8,10,1), Vector(0,0,height_screen/2,0),
                        Vector(-width_screen/2,0,0,0), Vector(0, focal_length,0,0));
    this->setCamera(camera_scene);

    // Screen
    Screen screen_scene(resolution_X, resolution_Y, camera_scene);
    this->setScreen(screen_scene);

}

/**
 * Load the scene1. Consist a white plane and a red sphere in front
 */
void Scene::load_scene1() {
    int resolution_X  = 16 * 52;
    int resolution_Y  = 9  * 52;
    int width_screen  = 16 *  4;
    int height_screen = 9  *  4;
    int focal_length  =  width_screen / (int)(2* tan(0.26 * M_PI)); // Fish Eye Avoidance Formula

    // Objects
    static Sphere sphere(Vector(15,10,10,1),5);
    shared_ptr<Emitter> sphere_material = make_shared<Emitter>(RGB(1,0,0));
    sphere.set_material(sphere_material);

    static Plane plane(Vector(15,20,10,1), Vector(0,-1,0,0));
    shared_ptr<Emitter> plane_material = make_shared<Emitter>(RGB(0.3,0.3,0.3));
    plane.set_material(plane_material);

    Vector center_disk(15, 10, 20, 1);
    static Disk disk(center_disk, Plane(center_disk, Vector(0,0,-1,0)),3);
    shared_ptr<Emitter> disk_material = make_shared<Emitter>(RGB(0,0,0.5));
    disk.set_material(disk_material);

    static Triangle triangle(Vector(3,10, 10,1), Vector(1.5, 10, 8,1), Vector(3, 10, 8, 1));
    shared_ptr<Emitter> triangle_material = make_shared<Emitter>(RGB(0,0.8,0));
    triangle.set_material(triangle_material);

    Matrix matrix_mesh;
    matrix_mesh = Matrix::traslation(15, 10, 10);
    matrix_mesh = matrix_mesh * Matrix::scale(5,5,5);

    static list<Triangle> triangle_mesh =
            TriangleMeshes::get_triangles_with_textures_simple("../geometry/models/text.obj.3D",
                    "../geometry/models/text.mtl", matrix_mesh);

    cout<<"Loading objects...";
    list<CollisionObject*> list;
    //list.push_back(&plane);
    /*list.push_back(&sphere);
    list.push_back(&disk);
    list.push_back(&triangle);*/
    list.push_back(&triangle_mesh.front());
    for(auto & iterator : triangle_mesh){
        list.push_back(&iterator);
    }
    this->setObjectsList(list);
    cout<<"OK"<<endl;

    // Camera
    Camera camera_scene(Vector(15,-focal_length/1.8,10,1), Vector(0,0,height_screen/2,0),
            Vector(-width_screen/2,0,0,0), Vector(0, focal_length,0,0));
    this->setCamera(camera_scene);

    // Screen
    Screen screen_scene(resolution_X, resolution_Y, camera_scene);
    this->setScreen(screen_scene);

}

void Scene::setCamera(const Camera &camera) {
    this->camera = camera;
}

void Scene::setScreen(const Screen &screen) {
    this->screen = screen;
}

void Scene::setObjectsList(const list <CollisionObject*> &objectsList){
    this->objects_list = objectsList;
}


