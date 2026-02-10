
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "json.hpp"

#include <iostream>
#include <memory>

#include "Geometry.h"
#include "Light.h"
#include "Output.h"
#include "Camera.h"


#include <fstream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

class Geometry;
class Light;
class Output;

class RayTracer {
    public: 
        RayTracer(nlohmann::json j);
        // void colorPixel(unique_ptr<Geometry>, )
        void run();
    private:
        vector<unique_ptr<Geometry>> geometryObjs; 
        vector<unique_ptr<Light>> lightObjs; 
        vector<unique_ptr<Output>> outputObjs; 
        Camera camera;
};



int save_ppm(std::string file_name, const std::vector<double>& buffer, int dimx, int dimy);

#endif
