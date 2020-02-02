//
// Created by Sergio on 08/11/2019.
//

#include <cmath>
#include "Scene.h"
#include "../geometry/Sphere.h"
#include "../geometry/Plane.h"
#include "../geometry/Disk.h"
#include "../geometry/Triangle.h"
#include "../geometry/TriangleMeshes.h"

Scene::Scene(const std::list<CollisionObject*> &objectsList, const Camera &camera, const Screen &screen,
        const std::list<DotLight> lights)
        : objects_list(objectsList), camera(camera), screen(screen), lights(lights) {}

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
    bool collision = false;

    // Iterate on the list of objects in the scene
    for(const auto& object : this->objects_list){
        //If the ray intersects with the object
        collision = object->intersection(ray, t_intersection);
        //cout << "t_intersection: " << t_intersection << " | collision: " << collision << endl;
        if(collision){
            //If the point of intersection is less than the nearest point so far
            if(t_intersection < near_intersection){
                //cout << "near_intersection: " << t_intersection << endl;
                // The intersection point is updated
                near_intersection = t_intersection;
                collision_object = object;
            }
        }
    }
    // If he's at least collided with some object.
    if(near_intersection != INFINITY){
        // Obtain the intersection point
        intersection_point = Vector(ray.getOrigin() + (near_intersection * ray.getDirection()));
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
    // Shared variables for all scenes
    const int resolution_X  = 16 * 53; // Surface *203 | PC *120 | Tests *53
    const int resolution_Y  = 9 * 53;
    const int width_screen  = 16 *  4;
    const int height_screen = 9  *  4;
    const int focal_length  = 16*4 / (int)(2* tan(0.26 * M_PI)); // Fish Eye Avoidance Formula

    /** Objects **/
    cout<<"Loading objects...";
    list<CollisionObject*> objects;
    /** Cornell box **/
    static Plane left_wall(Vector(0,0,0,PT),Vector(1,0,0,VEC));
    left_wall.set_material(make_shared<Phong>(RGB(0.89, 0.01, 0.01), RGB(0.01, 0.01, 0.01), 1.0));
    objects.push_back(&left_wall);

    static Plane right_wall(Vector(30,0,0,PT),Vector(-1,0,0,VEC));
    right_wall.set_material(make_shared<Phong>(RGB(0.01, 0.89, 0.01),RGB(0.01, 0.01, 0.01), 1.0));
    objects.push_back(&right_wall);

    static Plane floor(Vector(0,0,0,PT),Vector(0,0,1,VEC));
    floor.set_material(make_shared<Phong>(RGB(0.80, 0.80, 0.80), RGB(0.01, 0.01, 0.01), 1.0));
    objects.push_back(&floor);

    static Plane ceil(Vector(0,0,30,PT),Vector(0,0,-1,VEC));
    ceil.set_material(make_shared<Phong>(RGB(0.80, 0.80, 0.80), RGB(0.01, 0.01, 0.01), 1.0));
    objects.push_back(&ceil);

    float min = 0, max = 30 - min;    // The minX and maxX point of the square light
    static Triangle triangle1(Vector(max,min,29,PT), Vector(min,min,29,PT), Vector(min,max,29,PT));
    static Triangle triangle2(Vector(min,max,29,PT), Vector(max,max,29,PT), Vector(max,min,29,PT));
    triangle1.set_material(make_shared<Emitter>(RGB::white));
    triangle2.set_material(make_shared<Emitter>(RGB::white));
    //objects.push_back(&triangle1);objects.push_back(&triangle2);

    static Plane background(Vector(0,30,0,PT), Vector(0,-1,0,VEC));
    background.set_material(make_shared<Phong>(RGB(0.80, 0.80, 0.80), RGB(0.01, 0.01, 0.01), 1.0));
    objects.push_back(&background);

    /** Objects **/
    //static Sphere sphere1(Vector(15,10,7,PT),5);
    //static RefractionPerfect refractionPerfect(RGB(0.45, 0.45, 0.45));
    //refractionPerfect.set_type(refraction_type::DIAMOND);
    //sphere1.set_material(make_shared<Composite>(Emitter(RGB(0,0,0)),
    //        Phong(RGB(0.0,0.0,0.0), RGB(0,0,0), 50),
    //        refractionPerfect,
    //        SpecularPerfect(RGB(0.45,0.45,0.45))
     //       ));
    //objects.push_back(&sphere1);

    static Sphere sphere3(Vector(15,26,4,PT),1);
    sphere3.set_material(make_shared<Phong>(RGB(0.8,0,0), RGB(0.1,0.1,0.1), 50));
    //sphere3.set_material(make_shared<RefractionPerfect>(RGB(0.9, 0.9, 0.9)));
    //objects.push_back(&sphere3);

    static Sphere sphere5(Vector(22,25,3,PT),2);
    sphere5.set_material(make_shared<SpecularPerfect>(RGB(0.9,0.9,0.0)));
    //objects.push_back(&sphere5);

    static Sphere sphereA(Vector(15,15,5,PT),5);
    static RefractionPerfect refractionPerfect(RGB(0.9, 0.9, 0.9));
    refractionPerfect.set_type(refraction_type::WATER);
    sphereA.set_material(make_shared<RefractionPerfect>(refractionPerfect));
    //objects.push_back(&sphereA);

    static Sphere sphereB(Vector(15,15,5,PT),5);
    sphereB.set_material(make_shared<Phong>(RGB(0.80,0.80,0.80), RGB(0.10, 0.10, 0.10), 30));
    objects.push_back(&sphereB);

    static Sphere sphereC(Vector(15,15,5,PT),5);
    sphereC.set_material(make_shared<SpecularPerfect>(RGB(0.9,0.9,0.9)));
    //objects.push_back(&sphereC);

    /*Matrix matrix_mesh;
    matrix_mesh = Matrix::traslation(15, 10, 10);
    matrix_mesh = matrix_mesh * Matrix::scale(5,5,5);

    static list<Triangle> triangle_mesh =
            TriangleMeshes::get_triangles_without_textures("../geometry/models/tesla.obj",
                                                               matrix_mesh);
    cout<<"Loading objects...";
    for(auto & iterator : triangle_mesh){
        objects.push_back(&iterator);
    }
    */
    this->setObjectsList(objects);
    cout<<"Objects loaded successfully"<<endl;

    /** Lights **/
    cout<<"Loading lights...";
    std::list<DotLight> dot_lights;
    // Dot light
    static DotLight light(Vector(15,15,25,PT), RGB::white, 100);
    dot_lights.push_back(light);

    this->setLights(dot_lights);
    cout<<"Lights loaded successfully"<<endl;

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
    // Shared variables for all scenes
    const int resolution_X  = 16 * 53;
    const int resolution_Y  =  9 * 53; // 462 for Robert PC
    const int width_screen  = 16 *  4;
    const int height_screen = 9  *  4;
    const int focal_length  =  16*4 / (int)(2* tan(0.26 * M_PI)); // Fish Eye Avoidance Formula

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

const list<DotLight> &Scene::getLights() const {
    return lights;
}

void Scene::setLights(const list<DotLight> &lights) {
    Scene::lights = lights;
}



/**
 * Return true if the collision point is occluded by an object between the light and the point in the shadow ray.
 * @param collision_point
 * @param light
 * @param shadow_ray
 * @return
 */
bool Scene::shadow_ray(const Ray &shadow_ray, const Vector &collision_point, const DotLight& light) const{
    Vector intersection_occluded_point;
    bool is_intersection = near_intersection(shadow_ray, intersection_occluded_point);
    if(is_intersection){
        return (light.getPosition() - collision_point).modulus() > (intersection_occluded_point - collision_point).modulus();
    }else{
        return false;
    }
}


