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

        // check geometry mandatory vars
        if (!containsMandatoryProperty(*itr, "type") ||
                (!containsMandatoryProperty(*itr, "ac")) ||
                (!containsMandatoryProperty(*itr, "dc")) ||
                (!containsMandatoryProperty(*itr, "sc")) ||
                (!containsMandatoryProperty(*itr, "ka")) ||
                (!containsMandatoryProperty(*itr, "kd")) ||
                (!containsMandatoryProperty(*itr, "ks")) ||
                (!containsMandatoryProperty(*itr, "pc"))){
                    return false;
            }
            
            type = (*itr)["type"].get<std::string>();

            Eigen::Vector3f ac = parseVector(*itr, "ac");
            Eigen::Vector3f dc = parseVector(*itr, "dc");
            Eigen::Vector3f sc = parseVector(*itr, "sc");
            float ka = parseFloat(*itr, "ka");
            float kd = parseFloat(*itr, "kd");
            float ks = parseFloat(*itr, "ks");
            float pc = parseFloat(*itr, "pc");
        
        if(type=="sphere"){
            cout<<"Sphere: "<<endl;

            // mandatory vars 
            if (!containsMandatoryProperty(*itr, "centre") ||
                (!containsMandatoryProperty(*itr, "radius"))){
                return false;
            }

            Eigen::Vector3f centre = parseVector(*itr, "centre");
            float radius = parseFloat(*itr,"radius");
            
            cout<<"Centre: \n"<<centre<<endl;
            cout<<"Radius: "<<radius<<endl;

        }
        else if (type == "rectangle"){
            cout<<"Rectangle: "<<endl;

            // mandatory vars 
            if (!containsMandatoryProperty(*itr, "p1") ||
                (!containsMandatoryProperty(*itr, "p2")) ||
                (!containsMandatoryProperty(*itr, "p3")) ||
                (!containsMandatoryProperty(*itr, "p4"))){
                    return false;
            }

            Eigen::Vector3f p1 = parseVector(*itr, "p1");
            Eigen::Vector3f p2 = parseVector(*itr, "p2");
            Eigen::Vector3f p3 = parseVector(*itr, "p3");
            Eigen::Vector3f p4 = parseVector(*itr, "p4");

            cout<<"p1: \n"<<p1<<endl;
            cout<<"p2: \n"<<p2<<endl;
            cout<<"p3: \n"<<p3<<endl;
            cout<<"p4: \n"<<p4<<endl;      
        }
            cout<<"ac: \n"<<ac<<endl;
            cout<<"dc: \n"<<dc<<endl;
            cout<<"sc: \n"<<sc<<endl;
            cout<<"ka: "<<ka<<endl;
            cout<<"kd: "<<kd<<endl;
            cout<<"ks: "<<ks<<endl;
            cout<<"pc: "<<pc<<endl;
        ++gc;
    }
    
    cout<<"We have: "<<gc<<" objects!"<<endl;
    return true;
}

bool parse_lights(json& j){
    cout<<"Light: "<<endl;
    int lc = 0;
    
    // use iterators to read-in array types
    for (auto itr = j["light"].begin(); itr!= j["light"].end(); itr++){
        
        std::string type;
        if (!containsMandatoryProperty(*itr, "type") ||
                (!containsMandatoryProperty(*itr, "id")) ||
                (!containsMandatoryProperty(*itr, "is"))){
                    return false;
            }
        
        type = (*itr)["type"].get<std::string>();

        Eigen::Vector3f id = parseVector(*itr, "id");
        Eigen::Vector3f is = parseVector(*itr, "is");

        if(type=="point"){
            cout<<"Point based light: "<<endl;

            if(!containsMandatoryProperty(*itr, "centre")){
                return false;
            }

            Eigen::Vector3f centre = parseVector(*itr, "centre");
            cout<<"Centre: \n"<<centre<<endl;
        }
        else if(type == "area"){
            cout<<"Area based light: "<<endl;

            if (!containsMandatoryProperty(*itr, "p1") ||
                (!containsMandatoryProperty(*itr, "p2")) ||
                (!containsMandatoryProperty(*itr, "p3")) ||
                (!containsMandatoryProperty(*itr, "p4"))){
                    return false;
            }

            Eigen::Vector3f p1 = parseVector(*itr, "p1");
            Eigen::Vector3f p2 = parseVector(*itr, "p2");
            Eigen::Vector3f p3 = parseVector(*itr, "p3");
            Eigen::Vector3f p4 = parseVector(*itr, "p4");

            cout<<"p1: \n"<<p1<<endl;
            cout<<"p2: \n"<<p2<<endl;
            cout<<"p3: \n"<<p3<<endl;
            cout<<"p4: \n"<<p4<<endl;
        }
        cout<<"id: \n"<<id<<endl;
        cout<<"is: \n"<<is<<endl;
        ++lc;
    }
    
    cout<<"We have: "<<lc<<" objects!"<<endl;
    
    return true;
}

bool parse_output(json& j){
    cout<<"Outputs: "<<endl;
    int lc = 0;
    
    // use iterators to read-in array types
    for (auto itr = j["output"].begin(); itr!= j["output"].end(); itr++){
        
        std::string filename;
    
        if (!containsMandatoryProperty(*itr, "filename") ||
                (!containsMandatoryProperty(*itr, "size")) ||
                (!containsMandatoryProperty(*itr, "fov")) ||
                (!containsMandatoryProperty(*itr, "centre")) ||
                (!containsMandatoryProperty(*itr, "up")) ||
                (!containsMandatoryProperty(*itr, "lookat")) ||
                (!containsMandatoryProperty(*itr, "ai")) ||
                (!containsMandatoryProperty(*itr, "bkc"))){
                    return false;
            }

        filename = (*itr)["filename"].get<std::string>();

        
        int size[2];
        int i = 0;
        for (auto itr2 =(*itr)["size"].begin(); itr2!= (*itr)["size"].end(); itr2++){
            if(i<2){
                size[i++] = (*itr2).get<float>();
            } else {
                cout<<"Warning: Too many entries in size"<<endl;
                return false;
            }
        }
        
        Eigen::Vector3f lookat = parseVector(*itr, "lookat");
        Eigen::Vector3f up = parseVector(*itr, "up");
        Eigen::Vector3f centre = parseVector(*itr, "centre");
        float fov = parseFloat(*itr, "fov");
        Eigen::Vector3f ai = parseVector(*itr, "ai");
        Eigen::Vector3f bkc = parseVector(*itr, "bkc");
        
        cout<<"Filename: " << filename << endl;
        cout << "Size: " << size[0] << ", " << size[1] << endl;
        cout << "Lookat: \n" << lookat << endl;
        cout << "up: \n" << up << endl;
        cout<<"FOV: "<<fov<<endl;
        cout << "Camera centre: \n" << centre << endl;
        cout << "ai: \n" << ai << endl;
        cout << "bkc: \n" << bkc << endl;
       
        ++lc;
    }
    
    cout<<"We have: "<<lc<<" objects!"<<endl;
    return true;
}

// Parses a vector from a json object
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

// Parses a float from a json object
float parseFloat(const json& jsonObj, const string& propertyName){
    if (!(jsonObj).contains(propertyName)){
        cout << propertyName << " does not exist, but no matter! Setting it as 0" << endl;
        return 0;
    }
    return (jsonObj)[propertyName].get<float>();
}

// checks for mandatory property
bool containsMandatoryProperty(const json& jsonObj, const string& property){
    if (!jsonObj.contains(property)){
        cerr<<"Warning: "<< property << " is mandatory" <<endl;
        return false;
    }   
    return true;
}
