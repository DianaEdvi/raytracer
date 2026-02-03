
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "json.hpp"

class RayTracer {
    public: 
        RayTracer(nlohmann::json j);
        void run();
};

#endif
