
#ifndef COMPUTERGRAPHICS_SCENE_H
#define COMPUTERGRAPHICS_SCENE_H

#include <list>
#include <memory>
#include "Camera.h"
#include "Screen.h"
#include "../geometry/CollisionObject.h"
#include "../imaging/DotLight.h"


/**
 * The scene class represents a 3D scene with its camera, its screen to project, its lights and its objects.
 */
class Scene {
private:
    std::list<CollisionObject*> objects_list;
    std::list<DotLight> lights;
    Camera camera;
    Screen screen;


public:
    Scene(const std::list<CollisionObject*> &objectsList, const Camera &camera, const Screen &screen,
            const std::list<DotLight> lights);
    Scene();

    const Camera &getCamera() const;
    const Screen &getScreen() const;
    void setObjectsList(const list <CollisionObject*> &objectsList);
    void setCamera(const Camera &camera);
    void setScreen(const Screen &screen);

    const list <DotLight> &getLights() const;

    void setLights(const list <DotLight> &lights);

    CollisionObject* near_intersection(const Ray &ray, Vector &intersection_point) const;

    bool shadow_ray(const Ray& shadow_ray, const Vector& collision_point, const DotLight& light) const;

    // List of scenes const harcoded&
    void load_cornellBox();
    void load_scene1();


};


#endif //COMPUTERGRAPHICS_SCENE_H
