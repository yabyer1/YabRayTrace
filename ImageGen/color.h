#ifndef COLOR_H
#define COLOR_H
#include "vec3.h"
#include <iostream>
using color = vec3;
void write_color(std:: ostream& out, const color& pixel_color){
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();
    //translate to byte range
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);
    //write the component
    out << rbyte << ' ' << gbyte << ' '<< bbyte << '\n';
}
#endif
