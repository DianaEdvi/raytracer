
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "json.hpp"

#include <iostream>
#include <memory>

#include "Geometry.h"
#include "Light.h"

using namespace std;

class Geometry;
class Light;
class RayTracer {
    public: 
        RayTracer(nlohmann::json j);
        void run();
    private:
        vector<unique_ptr<Geometry>> geometryObjs; 
        vector<unique_ptr<Light>> lightObjs; 
        // unique_ptr<Output> output; 
};

#endif
