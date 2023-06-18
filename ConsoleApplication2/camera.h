#ifndef CAMERA_H
#define CAMERA_H
#include <cmath>
#include "raytraceengine.h"
#include "ray.h"

class camera {
public:
    const double m_pi = 3.14159265358979323846;
    camera(vecfloat lookfrom, vecfloat lookat, vecfloat vup, float vfov, float aspect) {
        vecfloat u, v, w;
        float theta = vfov * m_pi / 180;
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;
        origin = lookfrom;
        w = (lookfrom - lookat).normalize();
        u = vup.cross_product(w).normalize();
        v = w.cross_product(u);
        lower_left_corner = origin - u * half_width - v * half_height - w;

        horizontal = u * 2.0 * half_width;
        vertical = v * 2.0 * half_height;
    }

    ray get_ray(float s, float t) {
        return ray(origin, lower_left_corner + horizontal * s + vertical * t - origin);
    }

    vecfloat origin;
    vecfloat lower_left_corner;
    vecfloat horizontal;
    vecfloat vertical;
};
#endif