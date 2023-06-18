#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

//hittable for each object
struct hit_record
{
    float t = 0.0f;
    vecfloat p;
    vecfloat normal;
};

class hittable
{
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif