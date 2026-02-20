#include "RayTracer.h"

#include "json.hpp"
#include "Utility.h"
#include "Geometry.h"
#include "Light.h"
#include "Output.h"
#include "Camera.h"
#include "Ray.h"
#include "Color.h"

#include <iostream>
#include <Eigen/Dense>

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

}

void RayTracer::run(){


    std::cout << *geometryObjs[0] << std::endl;

    for(auto& obj : outputObjs){
        Camera camera(
            obj->getLookat(),
            obj->getUp(),
            obj->getCentre(),
            obj->getFov(),
            obj->getWidth(),
            obj->getHeight()
          );
    
        int dimx = camera.getWidth();
        int dimy = camera.getHeight();
            
        std::vector<double> buffer(3*dimx*dimy);
        for(int i = 0; i < dimy; ++i){      // row y
            for(int j = 0; j < dimx; ++j){  // column x
                // Generate ray through this pixel
                Ray r = camera.getRay(i, j);
                Color pixelColor; // background by default
    
                float closestT = numeric_limits<float>::infinity();
                Geometry* closestObj = nullptr;
    
                for(auto& go : geometryObjs){
                    float currentT;
                    if (go->intersect(r.getOrigin(), r.getDirection(), currentT)){
                        if (currentT < closestT){ 
                            closestT = currentT;
                            closestObj = go.get(); 
                        }
                    }
                }
    
                if(closestObj){
                    pixelColor.r = closestObj->hitRecord->dc[0];
                    pixelColor.g = closestObj->hitRecord->dc[1];
                    pixelColor.b = closestObj->hitRecord->dc[2];
                }
    
                // write to buffer
                buffer[3*i*dimx + 3*j + 0] = pixelColor.r;
                buffer[3*i*dimx + 3*j + 1] = pixelColor.g;
                buffer[3*i*dimx + 3*j + 2] = pixelColor.b;
    
            }
        }

        
        save_new_ppm(obj->getFilename(), buffer, dimx, dimy);
        
    }

}

