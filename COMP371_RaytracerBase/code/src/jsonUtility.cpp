#include "jsonUtility.h"

#include <iostream>
#include <Eigen/Dense>

using namespace std;

bool parse_geometry(json& j){
    cout<<"Geometry: "<<endl;
    int gc = 0;
    
    // use iterators to read-in array types
    for (auto itr = j["geometry"].begin(); itr!= j["geometry"].end(); itr++){
        
        std::string type;
        if(itr->contains("type")){
           // type = static_cast<std::string>((*itr)["type"]);
            type = (*itr)["type"].get<std::string>();
        } else {
            cout<<"Fatal error: geometry should always contain a type!!!"<<endl;
            return false;
        }
        
        if(type=="sphere"){
            cout<<"Sphere: "<<endl;

            // mandatory vars 

            // Check if centre and radius properties exists 
            if (!containsMandatoryProperty(*itr, "centre") ||
                (!containsMandatoryProperty(*itr, "radius"))){
                return false;
            }

            Eigen::Vector3f centre = parseVector(*itr, "centre");
            cout<<"Centre: \n"<<centre<<endl;
    
            float radius = (*itr)["radius"].get<float>();
            cout<<"Radius: "<<radius<<endl;


            // Non mandatory vars
            Eigen::Vector3f ac = parseVector(*itr, "ac");
            Eigen::Vector3f dc = parseVector(*itr, "dc");
            Eigen::Vector3f sc = parseVector(*itr, "sc");
            float ka = parseFloat(*itr, "ka");
            float kd = parseFloat(*itr, "kd");
            float ks = parseFloat(*itr, "ks");
            float pc = parseFloat(*itr, "pc");

            cout<<"ac: \n"<<ac<<endl;
            cout<<"dc: \n"<<dc<<endl;
            cout<<"sc: \n"<<sc<<endl;
            cout<<"ka: "<<ka<<endl;
            cout<<"kd: "<<ka<<endl;
            cout<<"ks: "<<ks<<endl;
            cout<<"pc: "<<pc<<endl;
        }
        else if (type == "rectangle"){
            if (!containsMandatoryProperty(*itr, "p1") ||
                (!containsMandatoryProperty(*itr, "p2")) ||
                (!containsMandatoryProperty(*itr, "p3")) ||
                (!containsMandatoryProperty(*itr, "p4"))){
                    return false;
                }
        }
        ++gc;
    }
    
    cout<<"We have: "<<gc<<" objects!"<<endl;
    return true;
}

// Parses a vector from a json object
// Most of this code came from base proejct
Eigen::Vector3f parseVector(const json& jsonObj, const string& propertyName){
    Eigen::Vector3f vec(0,0,0);

    // Check if the property actually exists
    if (!jsonObj.contains(propertyName)) {
        cerr << "Property '" << propertyName << "' not found." << endl;
        return vec;
    }

    int i = 0;
    for (auto itr2 =(jsonObj)[propertyName].begin(); itr2!= (jsonObj)[propertyName].end(); itr2++){
        if(i<3){
            vec[i++] = (*itr2).get<float>();
        } else {
            cout<<"Warning: Too many entries in vector"<<endl;
        }
    }
    return vec;
}

float parseFloat(const json& jsonObj, const string& propertyName){
    if (!(jsonObj).contains(propertyName)){
        cout << propertyName << " does not exist, but no matter! Setting it as 0" << endl;
        return 0;
    }
    return (jsonObj)[propertyName].get<float>();
}

bool containsMandatoryProperty(const json& jsonObj, const string& property){
    string type = jsonObj["type"].get<string>();
    if (!jsonObj.contains(property)){
        cerr<<"Warning: "<< property << " is mandatory for " << type << " type"<<endl;
        return false;
    }   
    return true;
}