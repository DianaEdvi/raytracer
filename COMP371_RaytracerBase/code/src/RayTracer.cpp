#include "RayTracer.h"
#include "json.hpp"
#include "jsonUtility.h"

#include "Geometry.h"
#include "Light.h"
#include "Output.h"
#include "Camera.h"
#include "Ray.h"
#include "Color.h"


#include <iostream>
#include <Eigen/Dense>
#include <sstream>
#include <fstream>

#include <memory>

using namespace std;
using namespace nlohmann;

RayTracer::RayTracer(nlohmann::json j)
    : camera(
        Output(j["output"][0]).getLookat(),
        Output(j["output"][0]).getUp(),
        Output(j["output"][0]).getCentre(),
        Output(j["output"][0]).getFov(),
        Output(j["output"][0]).getWidth(),
        Output(j["output"][0]).getHeight()
      ){
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

    int dimx = camera.getWidth();
    int dimy = camera.getHeight();
    
    std::vector<double> buffer(3*dimx*dimy);
    for(int i = 0; i < dimy; ++i){      // row
        for(int j = 0; j < dimx; ++j){  // column
            // Generate ray through this pixel
            Ray r = camera.getRay(i, j);
            Color shapeColor(0.0,1.0,0.0);
            Color backgroundColor(1.0,0.0,0.0);

            float t;

            if (geometryObjs[0]->intersect(r.getOrigin(), r.getDirection(), t)){
                buffer[3*i*dimx + 3*j + 0] = shapeColor.r;  // R
                buffer[3*i*dimx + 3*j + 1] = shapeColor.g;  // G
                buffer[3*i*dimx + 3*j + 2] = shapeColor.b;  // B
            }
            else {
                // For testing, just set color backgroundColor
                buffer[3*i*dimx + 3*j + 0] = backgroundColor.r;  // R
                buffer[3*i*dimx + 3*j + 1] = backgroundColor.g;  // G
                buffer[3*i*dimx + 3*j + 2] = backgroundColor.b;  // B
            }
            // for(auto& go : geometryObjs){
            // }


        }
    }

    save_ppm("test.ppm", buffer, dimx, dimy);
}

int save_ppm(std::string file_name, const std::vector<double>& buffer, int dimx, int dimy) {
   
    ofstream ofs(file_name, ios_base::out | ios_base::binary);
    ofs << "P6" << endl << dimx << ' ' << dimy << endl << "255" << endl;
 
    for (unsigned int i = 0; i < dimy; ++i)
        for (unsigned int j = 0; j < dimx; ++j)
            ofs << (char) (255.0 * buffer[3*i*dimx+3*j+0]) <<  (char) (255.0 * buffer[3*i*dimx+3*j+1]) << (char) (255.0 * buffer[3*i*dimx+3*j+2]);
 
    ofs.close();
 
    return 0;
}


