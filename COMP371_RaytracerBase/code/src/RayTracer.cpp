#include "RayTracer.h"

#include "json.hpp"
#include <iostream>

RayTracer::RayTracer(nlohmann::json j){
    std::cout << "RAYTRACER CONSTRUCTORRRRRRR" << std::endl;
}

void RayTracer::run(){
    std::cout << "RUNRUNRUN" << std::endl;
}