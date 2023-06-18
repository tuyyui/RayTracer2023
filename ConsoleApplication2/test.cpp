#include <fstream>
#include <cmath>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <random>
#include "raytraceengine.h"

#include "sphere.h"

#include "hittablelist.h"
#include "camera.h"

vecfloat random_in_unit_sphere()
{

    vecfloat p(0, 0, 0);
    ///Random number generator for reflections
    std::random_device rd;

    std::uniform_real_distribution<> rn1(0, 1);
    std::uniform_real_distribution<> rn2(0, 1);
    std::uniform_real_distribution<> rn3(0, 1);
    do
    {
        std::mt19937 gen(rd());

        auto x = rn1(gen);
        auto y = rn2(gen);
        auto z = rn3(gen);
        //  std::cout << x << std::endl;
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        std::cout << z << std::endl;
        p = (vecfloat((float)x, (float)y, (float)z) * (float)2.0) - vecfloat(1.0f, 1.0f, 1.0f);

        std::cout << p.squared_length() << std::endl;
    } while (p.squared_length() <= float(1));
    std::cout << "it broke returning" << std::endl;
    return p;
}
vecfloat color(const ray& r, hittable_list* world)
{

    hit_record rec;

    if (world->hit(r, 0.0, 100.0, rec))
    {
        std::cout << "Is this working" << std::endl;
        vecfloat target = (rec.p + rec.normal) + random_in_unit_sphere();
        //Recursive function that models real time shadows
        return color(ray(rec.p, target - rec.p), world) * 0.5;
    }
    else
    {

        vecfloat unit_direction(0, 0, 0);
        unit_direction.unit_vector(r.direction());
        float t = 0.5 * (rec.normal.get_y() + 1.0);
        return vecfloat(1.0, 1.0, 1.0) * (float)(1.0 - t) + vecfloat(0.5, 0.7, 1.0) * t;
    }
}

void runProgram()
{

    int nx = 200;
    int ny = 100;
    float ns = 100;

    std::random_device rd;
    std::uniform_real_distribution<> rn1(0, 1);
    std::uniform_real_distribution<> rn2(0, 1);
    std::uniform_real_distribution<> rn3(0, 1);
    std::ofstream out("out.ppm");
    raycaster::camera cam;
    out << "P3\n"
        << nx << " " << ny << "\n255\n";

    vecfloat lower_left_corner(-2.0, -1.0, -1.0);
    vecfloat _horizontial(4.0, 0.0, 0.0);
    vecfloat vertical(0.0, 2.0, 0.0);
    vecfloat origin(0.0, 0.0, 0.0);
    hittable* list[2];
    vecfloat a1(0, 0, -1);
    vecfloat a2(0, -100.5, -1);
    list[0] = new sphere(a1, 0.5);
    list[1] = new sphere(a2, 100);
    hittable* world = new hittable_list(list, 2);

    for (int i = ny - 1; i >= 0; i--)
    {
        for (int j = 0; j < nx; j++)
        {
            vecfloat col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                std::mt19937 gen(rd());
                auto x = rn1(gen);
                auto y = rn2(gen);

                float u = float(j + x) / float(nx);
                float v = float(i + y) / float(ny);

                ray r(origin, (lower_left_corner + ((_horizontial * u) + (vertical * v))));

                vecfloat p = r.point_at_parameter(2.0);
                col += color(r, static_cast<hittable_list*>(world));
            }
            col /= float(ns);

            int ir = int(255.99 * col.get_x());
            int ig = int(255.99 * col.get_y());
            int ib = int(255.99 * col.get_z());
            out << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}