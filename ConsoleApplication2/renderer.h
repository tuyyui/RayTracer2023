#ifndef RENDERER_H
#define RENDERER_H
#include "raytraceengine.h"
#include "camera.h"
#include "sphere.h"
#include "hittablelist.h"
#include <fstream>
#include <thread>
class renderer {
public:
    renderer(int width, int height)
        : width(width), height(height), aspect_ratio(float(width) / float(height)) {}

    void render() {
    
        // Initialize objects and camera
        hittable* list[2];
        list[0] = new sphere(vecfloat(0, 0, -1), 0.5);
        list[1] = new sphere(vecfloat(0, -100.5, -1), 100);
        hittable* world = new hittable_list(list, 2);
        camera cam(vecfloat(-2, 2, 1), vecfloat(0, 0, -1), vecfloat(0, 1, 0), 90, aspect_ratio);

        // Create output file
        std::ofstream outfile("render.ppm");
        outfile << "P3\n" << width << " " << height << "\n255\n";

        // Create a boolen flag to control the animation thread
        bool rendering = true;

        //Spawn a thread for the animation 
        std::thread animation([&]() {
            while (rendering) {
                std::cout << "Rendering in progress..." << std::endl;
                //Show rendering in progress every second.
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            });
        // Render the scene
        for (int j = height - 1; j >= 0; j--) {
            for (int i = 0; i < width; i++) {
                float u = float(i) / float(width);
                float v = float(j) / float(height);
                ray r = cam.get_ray(u, v);
                vecfloat col = color(r, world);
                int ir = int(255.99 * col[0]);
                int ig = int(255.99 * col[1]);
                int ib = int(255.99 * col[2]);
                outfile << ir << " " << ig << " " << ib << "\n";
            }
        }

        outfile.close();
        // Rendering is done, stop the animation
        rendering = false;
        // Wait for the animation thread to finish
        if (animation.joinable()) {
            animation.join();
        }
    }

private:
    vecfloat color(const ray& r, hittable* world) {
        hit_record rec;
        if (world->hit(r, 0.0, FLT_MAX, rec)) {
            return vecfloat(rec.normal.get_x() + 1, rec.normal.get_y() + 1, rec.normal.get_z() + 1) * 0.5f;
        }
        else {
            vecfloat unit_direction = r.direction().normalize();
            float t = 0.5 * (unit_direction.get_y() + 1.0);
            return  vecfloat(1.0, 1.0, 1.0) * (1.0 - t)  + vecfloat(0.5, 0.7, 1.0) * t ;
        }
    }

    int width, height;
    float aspect_ratio;
};

#endif