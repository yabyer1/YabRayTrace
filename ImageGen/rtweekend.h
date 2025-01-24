#ifndef RTWEEKEND_H
#define RTWEEKEND_H
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;

const double infinity = std:: numeric_limits<double>::infinity();
const double pi = 3.1415926535897932384626;

inline double degrees_to_radians(double degrees){
    return degrees * pi / 180.0;
}
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"
#endif

