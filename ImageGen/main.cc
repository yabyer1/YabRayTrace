#include <iostream>
#include "vec3.h"
#include "color.h"
int main(){
    int image_width = 256;
    int image_height = 256;
    
    std::cout<<"P3\n"<<image_width<<' '<<image_height<<"\n255\n";
    for(int j = 0; j < image_height;j++){
        for(int i = 0; i < image_width; i++){
       //insantiate color
            auto pixel_color = color (double(i) / (image_width - 1),
                                      double(j) / (image_height - 1),
                                      0);
    // write out the color
                                      write_color(std::cout, pixel_color);
        }
    }
}
