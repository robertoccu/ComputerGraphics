
#include "Plane.h"
#include "../material/Emitter.h"

Plane::Plane(const Vector &point, const Vector &normal) : point(point), normal(normal){
    distance = - (Vector::dot(normal, point));
    this->material = make_shared<Emitter>(RGB(0,0,0));
}




bool Plane::intersection(const Ray &ray, float &t) {
    bool is_intersection = false;
    float dot_product = Vector::dot(normal, ray.getDirection());
    if(dot_product != 0){
        is_intersection = true;
        t = -(distance + Vector::dot(ray.getOrigin(), normal)) / dot_product;
    }else{
        is_intersection = false;
    }
    return is_intersection;
}

Vector Plane::get_normal(const Vector &collision_point) const {
    return normal;
}

RGB Plane::get_color_emitter() {
    return material->get_emision();
}

void Plane::set_material(const shared_ptr<Material>& material_object) {
    // If the material object is Emitter type
    if(dynamic_pointer_cast<Emitter>(material_object)){
        this->material = std::make_shared<Emitter>(material_object->get_emision());
    }
}


