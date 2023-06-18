#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable
{
public:

    ~sphere() { std::cout << "Destroying" << std::endl; };
    sphere(vecfloat cen, float r) : center(cen), radius(r) {}
 
    bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
protected:
    vecfloat center;
    float radius;
};

#endif