#include "RayTracer.h"
#include "json.hpp"
#include "jsonUtility.h"

#include "Geometry.h"
#include "Light.h"
#include "Output.h"
#include "Camera.h"
#include "Ray.h"


#include <iostream>
#include <Eigen/Dense>
#include <sstream>
#include <fstream>

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

        // cout << camera << endl;

        
    // test_save_ppm();

    int dimx = camera.getWidth();
    int dimy = camera.getHeight();
    
    std::vector<double> buffer(3*dimx*dimy);
    for(int i = 0; i < dimy; ++i){      // row
        for(int j = 0; j < dimx; ++j){  // column
            // Generate ray through this pixel
            Ray r = camera.getRay(i, j);

            float t;

            if (geometryObjs[0]->intersect(r.getOrigin(), r.getDirection(), t)){
                buffer[3*i*dimx + 3*j + 0] = 0.0;  // R
                buffer[3*i*dimx + 3*j + 1] = 0.0;  // G
                buffer[3*i*dimx + 3*j + 2] = 0.0;  // B
            }
            else {
                // For testing, just set color red
                buffer[3*i*dimx + 3*j + 0] = 1.0;  // R
                buffer[3*i*dimx + 3*j + 1] = 0.0;  // G
                buffer[3*i*dimx + 3*j + 2] = 0.0;  // B
            }

        }
    }

    save_ppm("test.ppm", buffer, dimx, dimy);

}

void RayTracer::run(){
    std::cout << "RUNRUNRUN" << std::endl;
}


int test_save_ppm(){
    int dimx = 800;
    int dimy = 600;
    
    int w = 100;
    
    std::vector<double> buffer(3*dimx*dimy);
    for(int j=0;j<dimy;++j){
        for(int i=0;i<dimx;++i){
            if(((i+j)/w)%2==0){
                buffer[3*j*dimx+3*i+0]=1;
                buffer[3*j*dimx+3*i+1]=1;
                buffer[3*j*dimx+3*i+2]=0;
            } else {
                buffer[3*j*dimx+3*i+0]=0;
                buffer[3*j*dimx+3*i+1]=1;
                buffer[3*j*dimx+3*i+2]=1;
            }
        }
    }
               
             
    save_ppm("test.ppm", buffer, dimx, dimy);
    
    return 0;
}


int save_ppm(std::string file_name, const std::vector<double>& buffer, int dimx, int dimy) {
   
    ofstream ofs(file_name, ios_base::out | ios_base::binary);
    ofs << "P6" << endl << dimx << ' ' << dimy << endl << "255" << endl;
 
    for (unsigned int j = 0; j < dimy; ++j)
        for (unsigned int i = 0; i < dimx; ++i)
            ofs << (char) (255.0 * buffer[3*j*dimx+3*i+0]) <<  (char) (255.0 * buffer[3*j*dimx+3*i+1]) << (char) (255.0 * buffer[3*j*dimx+3*i+2]);
 
    ofs.close();
 
    return 0;
}

