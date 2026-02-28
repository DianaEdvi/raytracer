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
#include <algorithm>

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
                HitRecord hitRecord;
                Color pixelColor; 
    
                float closestT = numeric_limits<float>::infinity();
                Geometry* closestObj = nullptr;
    
                for(auto& go : geometryObjs){
                    HitRecord tempRecord;
                    if (go->intersect(r.getOrigin(), r.getDirection(), tempRecord)){
                        if (tempRecord.t < closestT){ 
                            closestT = tempRecord.t;
                            closestObj = go.get(); 
                            hitRecord = tempRecord;
                        }
                    }
                }
    
                if(closestObj){
                    pixelColor = calculatePhongLighting(hitRecord, *obj);
                }
                else {
                    pixelColor = Color(1.0f, 1.0f, 1.0f); // background color
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

Color RayTracer::calculatePhongLighting(HitRecord& hitRecord, Output& output){
    Eigen::Vector3f ambient = output.getAi().cwiseProduct(hitRecord.ac) * hitRecord.ka;
    Eigen::Vector3f diffuse(0.0f, 0.0f, 0.0f); 
    Eigen::Vector3f specular(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f V = (output.getCentre() - hitRecord.hitPoint).normalized(); // vector from the hit point to the camera eye 

    Eigen::Vector3f shadowOrigin = hitRecord.hitPoint + hitRecord.normal * 0.01f; // offset the shadow ray origin to prevent shadow acne
    for (auto& light : lightObjs){
        Eigen::Vector3f lightDiffuse(0.0f, 0.0f, 0.0f); 
        Eigen::Vector3f lightSpecular(0.0f, 0.0f, 0.0f);

        std::vector<Eigen::Vector3f> samplePoints = light->getSamplePoints();
        for(auto& samplePoint : samplePoints){
            Eigen::Vector3f L = (samplePoint - hitRecord.hitPoint).normalized(); // vector from the hit point to the light source 
            float lambertian = std::max(0.0f, hitRecord.normal.dot(L)); // the angle between the normal and the light, set to 0 if pointing away from normal 
    
            for(auto& go : geometryObjs){
                HitRecord shadowRecord;
                if (go->intersect(shadowOrigin, L, shadowRecord)){
                    float distToLight = (samplePoint - hitRecord.hitPoint).norm();
                    if (shadowRecord.t < distToLight) {
                        lambertian = 0.0f; // in shadow, no diffuse or specular contribution from this light
                        break;
                    }
                }
            }
    
            lightDiffuse = lightDiffuse + light->getId().cwiseProduct(hitRecord.dc * hitRecord.kd * lambertian);
            if (lambertian > 0.0){
                Eigen::Vector3f H = (L + V).normalized(); // The reflectance vector. The direction the light is going after hitting the object
                float specAngle = std::max(0.0f, hitRecord.normal.dot(H)); // check if that ray is hitting the camera         
                lightSpecular = lightSpecular + light->getIs().cwiseProduct(hitRecord.sc) * hitRecord.ks * std::pow(specAngle, hitRecord.pc);
            }
        }
        diffuse += lightDiffuse/static_cast<float>(samplePoints.size());
        specular += lightSpecular/static_cast<float>(samplePoints.size());
    }


    Color color(ambient + diffuse + specular);    
    color.r = std::min(1.0f, std::max(0.0f, color.r));
    color.g = std::min(1.0f, std::max(0.0f, color.g));
    color.b = std::min(1.0f, std::max(0.0f, color.b));
    return color;
}


