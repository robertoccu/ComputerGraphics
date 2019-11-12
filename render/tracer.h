//
// Created by Sergio on 08/11/2019.
//

#ifndef COMPUTERGRAPHICS_TRACER_H
#define COMPUTERGRAPHICS_TRACER_H

#include <random>
#include <thread>
#include <atomic>
#include "../imaging/Image.h"
#include "Scene.h"

class tracer {
public:
    static Image ray_tracer(const Scene &scene, int paths_per_pixel);
private:
    static void worker_tracer(unsigned int pixel_row_initial, unsigned int pixel_row_final, Image &image,
            const Scene &scene, int paths_per_pixel);
    static RGB ray_tracer(const Ray &ray, const Scene &scene);

private:
    static std::atomic<int> threads_progress;
    static void show_progress(const unsigned int rows);
};


#endif //COMPUTERGRAPHICS_TRACER_H
