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
    if (!(parse_geometry(j) && parse_lights(j) && parse_output(j))){
        cerr << "WARNING: Json file does not contain all mandatory variables. Please review and run again." << endl;
    }

}

void RayTracer::run(){
    std::cout << "RUNRUNRUN" << std::endl;
}


