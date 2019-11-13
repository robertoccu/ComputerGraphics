//
// Created by Sergio on 08/11/2019.
//

#include <cmath>
#include <utility>
#include "Scene.h"
#include "../geometry/Sphere.h"
#include "../geometry/Plane.h"

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
    CollisionObject* collision_object = nullptr;

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
    shared_ptr<Emitter> sphere_emitter = make_shared<Emitter>(RGB(1,0,0));
    sphere.set_material(sphere_emitter);

    static Plane plane(Vector(15,20,10,1), Vector(0,-1,0,0));
    shared_ptr<Emitter> plane_emitter = make_shared<Emitter>(RGB(1,1,1));
    plane.set_material(plane_emitter);

    list<CollisionObject*> list;
    list.push_back(&sphere); list.push_back(&plane);
    this->setObjectsList(list);

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


