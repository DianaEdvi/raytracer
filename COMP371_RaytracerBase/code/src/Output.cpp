#include "Output.h"

#include <iostream>
#include <iomanip>
#include <Eigen/Dense>

#include "jsonUtility.h"
using namespace std;

Output::Output(json& j){
     
    int i = 0;
    for (auto itr2 = j["size"].begin(); itr2 != j["size"].end() && i < 2; ++itr2) {
        size[i++] = (*itr2).get<int>();
    }
    
    filename = j["filename"].get<string>();
    lookat = parseVector(j, "lookat");
    up = parseVector(j, "up");
    centre = parseVector(j, "centre");
    fov = j.value("fov", 0.0f);
    ai = parseVector(j, "ai");
    bkc = parseVector(j, "bkc");
    raysperpixel = parseRaysPerPixel(j, "raysperpixel");
    antialiasing = parseBool(j, "antialiasing");
    twosiderender = parseBool(j, "twosiderender");
    globalillum = parseBool(j, "globalillum");
}

ostream &operator<<(ostream &out, const Output &output){
    out << "Filename: " << output.filename << endl;
    out << "Size: " << output.size[0] << ", " << output.size[1] << endl;
    out << "Lookat: " << output.lookat.transpose() << endl;
    out << "Up: " << output.up.transpose() << endl;
    out << "FOV: " << output.fov << endl;
    out << "Camera centre: " << output.centre.transpose() << endl;
    out << "ai: " << output.ai.transpose() << endl;
    out << "bkc: " << output.bkc.transpose() << endl;
    out << "raysperpixel: " << output.raysperpixel.transpose() << endl;
    out << "antialiasing: " << (output.antialiasing ? "true" : "false") << endl;
    out << "twosiderender: " << (output.twosiderender ? "true" : "false") << endl;
    out << "globalillum: " << (output.globalillum ? "true" : "false") << endl;
    return out;
}

Output::~Output() {}