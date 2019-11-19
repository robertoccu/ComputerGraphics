//
// Created by Sergio on 08/11/2019.
//


#include "tracer.h"

// Atomic variable that contains the number of rows that are already finished.
std::atomic<int> tracer::threads_progress(0);

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
    unsigned number_threads = 2* std::thread::hardware_concurrency() + 1;
    //unsigned number_threads = 1;
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
        return collision_object->get_color_emitter();  // Now return the color emission
    }else{
        return RGB(0, 0, 0);    // Return black
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
    for(unsigned int row = pixel_row_initial; row <= pixel_row_final; row++){
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
            image.setPixel(row, column, RGB::average_colors(colors, paths_per_pixel));
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
        cout<< '\r' << (int) percentage <<" %";
        progress = threads_progress.load(std::memory_order_seq_cst);
        // For very long processes, establish a time between progress and progress.
        //std::this_thread::sleep_for (std::chrono::seconds(1));
    }
}
