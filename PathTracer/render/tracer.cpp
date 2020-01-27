//
// Created by Sergio on 08/11/2019.
//


#include "tracer.h"

#ifndef SHOW_PROGRESS
#define SHOW_PROGRESS true
#endif

#ifndef DEBUG
#define DEBUG false
#endif

// Atomic variable that contains the number of rows that are already finished.
std::atomic<int> tracer::threads_progress(0);
// Atomic variable to save the max value of the image
std::atomic<float> tracer::image_max_value(0);

/**
 * Main method that calculates the image of the scene.
 * It throws rays from the camera towards the screen and returns
 * the colour of the objects with which it has collided.
 * @param scene
 * @return image of the scene
 */
Image tracer::ray_tracer(const Scene &scene, int paths_per_pixel) {
    // Image creation
    Image image("RayTracer", 1, scene.getScreen().getPixelsColumn(), scene.getScreen().getPixelsRow(),
            65535);

    /* Obtain the max number of cores
     * If you want to set the number of cores, change the variable and leave it at a fixed value */
    unsigned number_threads;
    #if DEBUG
        number_threads = 1;
    #else
        number_threads = 2 * std::thread::hardware_concurrency() + 1;
    #endif
    cout<<"Launching path tracer with "<<number_threads<<" workers"<<endl;
    // We check if the rows can be divided by the cores.
    // If it is not divisible, there will be some row that is not generated. Program will stop.
    if((scene.getScreen().getPixelsRow() % number_threads) != 0){
        cerr<<"You can't divide the number of columns by the cores that you have"<<endl;
        cerr<<"Change the number of cores OR the resolution_Y in scene"<<endl;
        exit(1);
    }

    // Obtain the number of rows for worker
    unsigned int rows_for_worker = scene.getScreen().getPixelsRow() / number_threads;
    // Create a vector of threads
    std::thread workers[number_threads + 1];
    // We launched all the workers
    for(int i = 0; i < number_threads; i++){
        workers[i] = std::thread(&worker_tracer, i * rows_for_worker, (i * rows_for_worker) + rows_for_worker - 1,
                ref(image), ref(scene), paths_per_pixel);
    }
    workers[number_threads] = std::thread(&show_progress, scene.getScreen().getPixelsRow());
    // We hope that it will be finished.
    for(int i = 0; i < number_threads; i++){
        workers[i].join();
    }
    workers[number_threads].join();
    cout<<"\n100 %"<<endl;
    cout<<"Path tracer finish"<<endl;
    cout<<"Image max value: "<<image_max_value<<endl;
    image.setMaxValue(image_max_value);
    return image;
}

/**
 * Trace the ray and check the intersections.
 * @param ray
 * @param scene
 * @return color of the ray
 */
RGB tracer::ray_tracer(const Ray &ray, const Scene &scene) {
#ifndef ABSORPTION_PROBABILITY
#define ABSORPTION_PROBABILITY 0.1
#endif

    Vector collision_point;
    // Obtain the collision object and the collision point
    CollisionObject* collision_object = scene.near_intersection(ray, collision_point);
    // If the ray was intersection
    if(collision_object != nullptr){
        // Path tracing
        // Lo = Le + { Li * Fr }
        RGB color(0,0,0);

        // Collision happened, so calculate next ray. Receive color from collision.
        Ray out_ray;
        float rr = Prng::random(); // Russian Roulette

        // Color at the collision point
        if (collision_object->get_material()->get_material() == material_type::EMITTER) {
            return collision_object->get_material()->get_emision();
        } else {
            color = collision_object->get_material()->get_outgoing_ray(ray, collision_object->get_normal(collision_point), collision_point, out_ray, rr);
        }

        // Next event estimation, only for phong material
        RGB next_event = next_event_estimation(scene, ray, collision_point, collision_object->get_normal(collision_point), collision_object->get_material());

        // Russian Roulette
        if (rr < 1 - ABSORPTION_PROBABILITY) {
            // Color = Li(out_ray) * BRDF() + next_event
            color = ray_tracer(out_ray, scene) * (color + next_event);
        } else  { // Ray discarded by Russian Roulette
            color = next_event;
        }

        return color;

    } else {
        return RGB::black;    // Return black
    }
}

/**
 * Each worker has the task of completing x rows of the image.
 * @param pixel_row_initial Row in which the worker must start working
 * @param pixel_row_final Row in which the worker must end working, included
 * @param image Image to store the result
 * @param scene Scene with the all parameters
 */
void tracer::worker_tracer(unsigned int pixel_row_initial, unsigned int pixel_row_final, Image &image,
        const Scene &scene, int paths_per_pixel){
    RGB colors[paths_per_pixel];
    Vector pixel;
    Ray ray;
    RGB pixel_color;
    float max_pixel_color_value;
    for(unsigned int row = pixel_row_initial; row <= pixel_row_final; row++){
        // Update the progress of the actual worker
        threads_progress.fetch_add(1);
        for(int column = 0; column < scene.getScreen().getPixelsColumn(); column++){
            for(int path = 0; path != paths_per_pixel; path++){
                // Obtain the pixel in world coordinates with a random offset
                pixel = scene.getScreen().get_pixel(row, column);
                // Create the ray
                ray = ray.rayFromPoints(scene.getCamera().getPosition(), pixel);
                // Obtain the color result of the intersection and save in the vector
                colors[path] = ray_tracer(ray, scene);
            }
            // Set the color result in the image
            pixel_color = RGB::average_colors(colors, paths_per_pixel);
            max_pixel_color_value = pixel_color.get_max_color();
            if (max_pixel_color_value > image_max_value.load()) {
                image_max_value.store(max_pixel_color_value);
            }
            image.setPixel(row, column, pixel_color);
        }
    }
}

/**
 *
 * @param rows
 */
void tracer::show_progress(const unsigned int rows){
    int progress = 0;
    float percentage;
    while(progress < rows - 1){
        // The percentage is calculated by rows
        percentage =  progress * 100.0 / (float) rows;
        #if SHOW_PROGRESS && !DEBUG
            cout<<(int) percentage <<" %"<<endl;
        #endif
        progress = threads_progress.load(std::memory_order_seq_cst);
        // For very long processes, establish a time between progress and progress.
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }
}

/**
 *
 * @param scene
 * @param in_ray
 * @param collision_point
 * @param normal
 * @return
 */
RGB tracer::next_event_estimation(const Scene &scene, const Ray &in_ray, const Vector &collision_point,
                                  const Vector &normal, shared_ptr<Material> material){
    RGB color_estimation(0, 0, 0);
    for(const auto& light : scene.getLights()){
        // Trace a ray of shadow between the collision point and the lights.
        Ray shadow_ray(collision_point + (0.01 * normal), (light.getPosition() - collision_point).normalize());
        // If the ray is occluded there is no light
        if(scene.shadow_ray(shadow_ray, collision_point, light)){
            continue;
        }
        // The shadow ray is not occluded
        RGB evaluate_render_equation = material->get_BRDF_next_event(in_ray, normal, shadow_ray, light, collision_point);
        color_estimation = color_estimation + evaluate_render_equation;
    }
    return color_estimation;
}
