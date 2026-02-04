#include "jsonUtility.h"

#include <iostream>
#include <Eigen/Dense>

using namespace std;

bool parse_geometry(json& j){
    int gc = 0;

    if (!containsMandatoryProperty(j, "geometry")){
        return false;
    }
    
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

        if(type=="sphere"){
            // mandatory vars 
            if (!containsMandatoryProperty(*itr, "centre") ||
                (!containsMandatoryProperty(*itr, "radius"))){
                return false;
            }
        }
        else if (type == "rectangle"){
            // mandatory vars 
            if (!containsMandatoryProperty(*itr, "p1") ||
                (!containsMandatoryProperty(*itr, "p2")) ||
                (!containsMandatoryProperty(*itr, "p3")) ||
                (!containsMandatoryProperty(*itr, "p4"))){
                    return false;
            }
    
        }
        ++gc;
    }
    
    cout<<"We have: "<<gc<<" Geometry objects, and all mandatory vars are there!"<<endl;
    return true;
}

bool parse_lights(json& j){
    int lc = 0;

     if (!containsMandatoryProperty(j, "light")){
        return false;
    }
    
    // use iterators to read-in array types
    for (auto itr = j["light"].begin(); itr!= j["light"].end(); itr++){
        
        std::string type;
        if (!containsMandatoryProperty(*itr, "type") ||
                (!containsMandatoryProperty(*itr, "id")) ||
                (!containsMandatoryProperty(*itr, "is"))){
                    return false;
            }
        
        type = (*itr)["type"].get<std::string>();

        if(type=="point"){
            if(!containsMandatoryProperty(*itr, "centre")){
                return false;
            }
        }
        else if(type == "area"){
            if (!containsMandatoryProperty(*itr, "p1") ||
                (!containsMandatoryProperty(*itr, "p2")) ||
                (!containsMandatoryProperty(*itr, "p3")) ||
                (!containsMandatoryProperty(*itr, "p4"))){
                    return false;
            }
        }
        ++lc;
    }
    
    cout<<"We have: "<<lc<<" Light objects, and all mandatory vars are there!"<<endl;
    
    return true;
}

bool parse_output(json& j){
    cout<<"Outputs: "<<endl;
    int lc = 0;

     if (!containsMandatoryProperty(j, "output")){
        return false;
    }
    
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

        // optional vals
        Eigen::Vector3i raysperpixel = parseRaysPerPixel(*itr, "raysperpixel");
        bool antialiasing = parseBool(*itr, "antialiasing");
        bool twosiderender = parseBool(*itr, "twosiderender");
        bool globalillum = parseBool(*itr, "globalillum");

        cout<<"Filename: " << filename << endl;
        cout << "Size: " << size[0] << ", " << size[1] << endl;
        cout << "Lookat: \n" << lookat << endl;
        cout << "up: \n" << up << endl;
        cout<<"FOV: "<<fov<<endl;
        cout << "Camera centre: \n" << centre << endl;
        cout << "ai: \n" << ai << endl;
        cout << "bkc: \n" << bkc << endl;
        cout << "raysperpixel: \n" << raysperpixel << endl;
        cout << "antialiasing: " << antialiasing << endl;
        cout << "twosiderender: " << twosiderender << endl;
        cout << "globalillum: " << globalillum << endl;


       
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
        // cout << propertyName << " does not exist, but no matter! Setting it as 0" << endl;
        return 0;
    }
    return (jsonObj)[propertyName].get<float>();
}

// Parses a4x4 matrix from a json object
Eigen::Matrix4f parseMatrix4f(const json& jsonObj, const string& propertyName){
    Eigen::Matrix4f mat = Eigen::Matrix4f::Identity();

    // Check if the property actually exists
    if (!jsonObj.contains(propertyName)) {
        // cerr << "transform does not exist, but no matter! Setting it as identity" << endl;
        return mat;
    }

    int i = 0;
    for (auto itr = jsonObj[propertyName].begin();
         itr != jsonObj[propertyName].end();
         ++itr)
    {
        if (i < 16) {
            mat(i / 4, i % 4) = (*itr).get<float>();
            ++i;
        } else {
            cout << "Warning: Too many entries in matrix" << endl;
            break;
        }
    }

    if (i < 16) {
        cout << "Warning: Matrix has fewer than 16 values" << endl;
    }

    return mat;
}

bool parseBool(const json& jsonObj, const string& propertyName){
    if (!(jsonObj).contains(propertyName)){
            // cout << propertyName << " does not exist, but no matter! Setting it as false" << endl;
            return false;
        }
        return true;
}

// parse rays per pixel depending on the amount of entries in vector
Eigen::Vector3i parseRaysPerPixel(const json& jsonObj, const string& propertyName) {
    Eigen::Vector3i rpp(0, 0, 0); // initialize all to 0

    if (jsonObj.contains("raysperpixel")) {
        const auto& arr = jsonObj["raysperpixel"];

        if (!arr.is_array()) {
            std::cerr << "Error: 'raysperpixel' must be an array!" << std::endl;
            return rpp;
        }

        int i = 0;
        for (const auto& val : arr) {
            if (i < 3) {
                rpp[i++] = val.get<unsigned int>();
            } else {
                cerr << "Warning: 'raysperpixel' has more than 3 values; extra ignored." << endl;
                break;
            }
        }
    } else {
        // cout << "raysperpixel does not exist, but no matter! Setting its default to 1" << endl;
        rpp[0] = 1;
    }

    return rpp;
}


// checks for mandatory property
bool containsMandatoryProperty(const json& jsonObj, const string& property){
    if (!jsonObj.contains(property)){
        cerr<<"Warning: "<< property << " is mandatory" <<endl;
        return false;
    }   
    return true;
}
