#ifndef RAY_H
#define RAY_H
#include "raytraceengine.h"
#include <cmath>

class ray
{
public:
 
    ray(vecfloat a, vecfloat b) : A(a), B(b) {};
    //Both A and B are returning a Vector<T> value.
    vecfloat origin() const noexcept { return A; }
    vecfloat direction() const noexcept { return B; }
    vecfloat point_at_parameter(float t) const { return A + B * t; }
    vecfloat color(const ray& r, vecfloat unit_direction);

private:
    vecfloat A;
    vecfloat B;
};

#endif