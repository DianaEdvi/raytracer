
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "json.hpp"

#include <iostream>
#include <memory>

#include "Geometry.h"
#include "Light.h"
#include "Output.h"

using namespace std;

class Geometry;
class Light;
class Output;

class RayTracer {
    public: 
        RayTracer(nlohmann::json j);
        void run();
    private:
        vector<unique_ptr<Geometry>> geometryObjs; 
        vector<unique_ptr<Light>> lightObjs; 
        vector<unique_ptr<Output>> outputObjs; 
};

#endif
