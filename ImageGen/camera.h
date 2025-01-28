#ifndef CAMERA_H
#define CAMERA_H
#include "hittable.h"
#include "material.h"
class camera{
public:
    int max_depth = 10;
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;
    double vfov = 90; //vertical view angle
    point3 lookfrom = point3(0,0,0); //camera looking from
    point3 lookat = point3(0,0,-1); // camera is looking at
    vec3 vup = vec3(0,1,0); // camera relative up direction
    double defocus_angle = 0; // angles of rays through pixel
    double focus_dist  = 10; // distance from where we are loooking from to plane of perfect focus

    void render(const hittable& world){
        initialize();
        std::cout<<"P3\n"<<image_width<<' '<<image_height<<"\n255\n";
        for(int j = 0; j < image_height; j++){
         
            for(int i = 0; i < image_width; i++){
                color pixel_color(0,0,0);
                for(int sample = 0; sample < samples_per_pixel; sample++){
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }
    }
private:
    int image_height;
    point3 center;
    point3 pixel00_loc;
    double pixel_samples_scale;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    vec3 u,v,w; // camera frame basis vectors
    vec3 defocus_disk_u; // defocus disk horizontal radius
    vec3 defocus_disk_v; // defocus disk vertical radius
    void initialize(){
        image_height = int(image_width / aspect_ratio);
        if(image_height <1)
            image_height = 1;
        pixel_samples_scale = 1.0 / samples_per_pixel;
        center = lookfrom;
      
        auto theta = degrees_to_radians(vfov);
        auto h = std::tan(theta/ 2); //assuming -z is 2 we can calculate h to be of this ratio
        auto viewport_height = 2 * h * focus_dist;
        
        auto viewport_width = viewport_height * (double(image_width) / image_height);
        
        w = unit_vector(lookfrom - lookat);
        u = unit_vector((cross(vup, w)));
        v = cross(w, u);
        
        vec3 viewport_u = viewport_width * u; //vector across viewport horizontal edge
        vec3 viewport_v = viewport_height * -v; //vector down viewport vertical edge
        
        pixel_delta_u = viewport_u / image_width; //horiz and vert delta vectors
        pixel_delta_v = viewport_v / image_height;
        
        auto viewport_upper_left = center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left  + 0.5 * (pixel_delta_u + pixel_delta_v);
        //camera defocus
        auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
        
    }
    ray get_ray(int i, int j ) const{
        //camera ray from disk directed at a random point around i and j
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u)
        + ((j + offset.y()) * pixel_delta_v);
        auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
    }
    point3 defocus_disk_sample() const{
        auto p = random_in_unit_disk();
        return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }
    vec3 sample_square() const{
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
    color ray_color(const ray& r, int depth,  const hittable& world) const{
        if(depth <= 0){ // base case return no more light as too many bounces
            return color(0,0,0);
        }
        hit_record rec;
        if(world.hit(r, interval(0.001, infinity), rec)){
            ray scattered;
            color attenuation;
            if(rec.mat -> scatter(r, rec, attenuation, scattered)){
                return attenuation * ray_color(scattered, depth - 1, world);
            }
            return color(0,0,0);
        }
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0,1.0,1.0) + a*color(0.5, 0.7,1.0);
    }
};
#endif
