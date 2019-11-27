//
// Created by Sergio on 08/11/2019.
//

#ifndef COMPUTERGRAPHICS_TRACER_H
#define COMPUTERGRAPHICS_TRACER_H

#include <thread>
#include <atomic>
#include "../imaging/Image.h"
#include "Scene.h"
#include "../utils/Prng.h"

class tracer {
public:
    static Image ray_tracer(const Scene &scene, int paths_per_pixel);
private:
    static void worker_tracer(unsigned int pixel_row_initial, unsigned int pixel_row_final, Image &image,
            const Scene &scene, int paths_per_pixel);
    static RGB ray_tracer(const Ray &ray, const Scene &scene, bool camera_ray);
    static RGB next_event_estimation(const Scene &scene, const Ray &in_ray, const Vector &collision_point,
                                     const Vector &normal, shared_ptr<Material> material) ;

private:
    static std::atomic<int> threads_progress;
    static std::atomic<float> image_max_value;
    static void show_progress(const unsigned int rows);
};


#endif //COMPUTERGRAPHICS_TRACER_H
