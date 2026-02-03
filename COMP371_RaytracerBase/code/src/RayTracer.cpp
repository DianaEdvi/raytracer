#include "RayTracer.h"
#include "json.hpp"
#include "simpleppm.h"
#include "jsonUtility.h"


#include <iostream>
#include <Eigen/Dense>
#include <sstream>

using namespace std;
using namespace nlohmann;

RayTracer::RayTracer(nlohmann::json j){
    std::cout << "RAYTRACER CONSTRUCTORRRRRRR" << std::endl;
    parse_geometry(j);
}

void RayTracer::run(){
    std::cout << "RUNRUNRUN" << std::endl;
}


