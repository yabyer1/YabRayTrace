#ifndef HITTABLE_H
#define HITTABLE_H
#include "ray.h"
class hit_record{
public: point3 p;
    vec3 normal;
    double t;
    bool front_face;
    void set_face_normal(const ray& r, const vec3& outward_normal){
        // sets the hit record normal vector, if the direction of the normal vector and the ray is the same side then we know its inside the object else outside object
        front_face = (dot(r.direction(), outward_normal) < 0);
            normal = front_face ? outward_normal : -outward_normal;
        
    }
};
class hittable {
public: 
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};
#endif
