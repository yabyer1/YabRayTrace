#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"
color ray_color(const ray& r){
    //blended value = (1 - a) * startValue + a * endvalue
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0); // a must be in the range [0, 1], so we need to normalize direction vector giving it [-1, 1] then add 1 and multiply by .5
    //gradient from color1 to color2
    return (1.0 - a ) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}
int main(){
    auto aspect_ratio = 16.0 / 9.0;
    
    int image_width = 256;
   
    //image height from width and ratio and must be 1 at the very least
    int image_height = (int) (image_width / aspect_ratio);
    if(image_height < 1)
        image_height = 1;
    //camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double (image_width) / image_height);
    auto camera_center = point3(0,0,0);
    //vectors across horizontal and vertical viewport edges
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;
    
    auto viewport_upper_left = camera_center - vec3(0,0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixell00_loc = viewport_upper_left + .5 * (pixel_delta_u + pixel_delta_v);
    
    std::cout<<"P3\n"<<image_width<<' '<<image_height<<"\n255\n";
    for(int j = 0; j < image_height;j++){
        for(int i = 0; i < image_width; i++){
       //insantiate color
            auto pixel_center = pixell00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
    // write out the color
                                      write_color(std::cout, pixel_color);
        }
    }
}
