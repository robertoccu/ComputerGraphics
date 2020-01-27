//
// Created by Sergio on 08/11/2019.
//

#ifndef COMPUTERGRAPHICS_COLLISIONOBJECT_H
#define COMPUTERGRAPHICS_COLLISIONOBJECT_H

#include "Ray.h"
#include "../material/Material.h"
#include <memory>

/**
 * An abstract class that represents any object that can be collided with lightning.
 */
class CollisionObject{
protected:
    std::shared_ptr<Material> material; // Pointer to the material of the object
public:
    virtual bool intersection(const Ray &ray, float &t) = 0;
    virtual Vector get_normal(const Vector& collision_point) const = 0;
public:
    /**
     * Return the color emitter of the object
     * @return
     */
    RGB get_color_emitter(){
        return material->get_emision();
    }

    /**
     * Set the material of the object
     * @param material_object shared_ptr
     */
    void set_material(const shared_ptr<Material>& material_object) {
        this->material = material_object;
    }

    /**
     * Return the material of the object
     * @return
     */
    shared_ptr<Material> get_material(){return this->material;}
};

#endif //COMPUTERGRAPHICS_COLLISIONOBJECT_H
