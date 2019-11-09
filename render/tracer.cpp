//
// Created by Sergio on 08/11/2019.
//

#include "tracer.h"

/**
 * Main method that calculates the image of the scene.
 * It throws rays from the camera towards the screen and returns
 * the colour of the objects with which it has collided.
 * @param scene
 * @return image of the scene
 */
Image tracer::ray_tracer(const Scene &scene) {
    // Image creation
    Image image("RayTracer", 1, scene.getScreen().getPixelsColumn(), scene.getScreen().getPixelsRow(),
            65535);
    RGB color;
    float percentage;

    for(int row = 0; row < scene.getScreen().getPixelsRow(); row++){
        // The percentage is calculated by rows
        percentage = 100 * ((float) row / (float) scene.getScreen().getPixelsRow());
        cout<< "\r" << (int) percentage <<" %"<<endl;

        for(int column = 0; column < scene.getScreen().getPixelsColumn(); column++){
            // Obtain the pixel in world coordinates
            Vector pixel = scene.getScreen().get_pixel(row, column);
            // Create the ray
            Ray ray; ray = ray.rayFromPoints(scene.getCamera().getPosition(), pixel);
            // Obtain the color result of the intersection
            color = ray_tracer(ray, scene);
            // Set the color result in the image
            image.setPixel(row, column, color);

        }
    }
    cout<< "\r" <<"100 %"<<endl;
    return image;
}

/**
 * Trace the ray and check the intersections.
 * @param ray
 * @param scene
 * @return color of the ray
 */
RGB tracer::ray_tracer(const Ray &ray, const Scene &scene) {
    Vector collision_point;
    // Obtain the collision object and the collision point
    CollisionObject* collision_object = scene.near_intersection(ray, collision_point);
    // If the ray was intersection
    if(collision_object != nullptr){
        return collision_object->getEmision();  // Now return the color emission
    }else{
        return RGB(0, 0, 0);    // Return black
    }
}
