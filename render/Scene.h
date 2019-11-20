
#ifndef COMPUTERGRAPHICS_SCENE_H
#define COMPUTERGRAPHICS_SCENE_H

#include <list>
#include <memory>
#include "Camera.h"
#include "Screen.h"
#include "../geometry/CollisionObject.h"


/**
 * The scene class represents a 3D scene with its camera, its screen to project, its lights and its objects.
 */
class Scene {
private:
    std::list<CollisionObject*> objects_list;
    Camera camera;
    Screen screen;


public:
    Scene(const std::list<CollisionObject*> &objectsList, const Camera &camera, const Screen &screen);
    Scene();

    const Camera &getCamera() const;
    const Screen &getScreen() const;
    void setObjectsList(const list <CollisionObject*> &objectsList);
    void setCamera(const Camera &camera);
    void setScreen(const Screen &screen);

    CollisionObject* near_intersection(const Ray &ray, Vector &intersection_point) const;

    // List of scenes harcoded
    void load_cornellBox();
    void load_scene1();


};


#endif //COMPUTERGRAPHICS_SCENE_H
