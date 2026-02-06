#include "RayTracer.h"
#include "json.hpp"
#include "simpleppm.h"
#include "jsonUtility.h"

#include "Geometry.h"
#include "Light.h"
#include "Output.h"
#include "Camera.h"


#include <iostream>
#include <Eigen/Dense>
#include <sstream>

#include <memory>

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

    for (auto itr = j["output"].begin(); itr!= j["output"].end(); itr++){
        outputObjs.push_back(make_unique<Output>(*itr));
    }


    // for(const auto& g : geometryObjs){
    //     cout << *g << endl;
    // }

    // for(const auto& l : lightObjs){
    //     cout << *l << endl;
    // }

    // for(const auto& o : outputObjs){
    //     cout << *o << endl;
    // }

    Camera camera(outputObjs[0]->getLookat(),
        outputObjs[0]->getUp(),
        outputObjs[0]->getCentre(),
        outputObjs[0]->getFov(), 
        outputObjs[0]->getWidth(),
        outputObjs[0]->getHeight());

        cout << camera << endl;


}

void RayTracer::run(){
    std::cout << "RUNRUNRUN" << std::endl;
}


