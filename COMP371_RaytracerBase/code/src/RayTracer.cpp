#include "RayTracer.h"
#include "json.hpp"
#include "simpleppm.h"
#include "jsonUtility.h"

#include "Geometry.h"
#include "Light.h"


#include <iostream>
#include <Eigen/Dense>
#include <sstream>

using namespace std;
using namespace nlohmann;

RayTracer::RayTracer(nlohmann::json j){
    if (!(parse_geometry(j) && parse_lights(j) && parse_output(j))){
        cerr << "WARNING: Json file does not contain all mandatory variables. Please review and run again." << endl;
        return;
    }

    GeometryFactory gf;
    LightFactory lf;

    for (auto itr = j["geometry"].begin(); itr!= j["geometry"].end(); itr++){
        
        geometryObjs.push_back(gf.create(*itr));
    }

    for (auto itr = j["light"].begin(); itr!= j["light"].end(); itr++){
        lightObjs.push_back(lf.create(*itr));
    }


    for(const auto& g : geometryObjs){
        cout << *g << endl;
    }

    for(const auto& l : lightObjs){
        cout << *l << endl;
    }



}

void RayTracer::run(){
    std::cout << "RUNRUNRUN" << std::endl;
}


