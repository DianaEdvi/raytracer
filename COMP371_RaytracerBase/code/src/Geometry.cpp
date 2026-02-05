#include "Geometry.h"

#include "jsonUtility.h"
#include "json.hpp"

#include <iostream>

using namespace nlohmann;
using namespace std;

unique_ptr<Geometry> GeometryFactory::create(json& j) {
    string type = j["type"].get<string>();

    if (type == "sphere"){
        return make_unique<Sphere>(j);
    }
    else if (type == "rectangle"){
        return make_unique<Rectangle>(j);
    }    

    throw std::runtime_error("Unknown geometry type: " + type);
}

Geometry::Geometry(json& j){
    ac = parseVector(j, "ac");
    dc = parseVector(j, "dc");
    sc = parseVector(j, "sc");
    ka = j.value("ka", 0.0);
    kd = j.value("kd", 0.0);
    ks = j.value("ks", 0.0);
    pc = j.value("pc", 0.0);
    visible = j.value("visible", true);
    transformMatrix = parseMatrix4f(j, "transform");
}

void Geometry::print(ostream& out) const {
    out << "ac: " << ac.transpose() << endl
        << "dc: " << dc.transpose() << endl
        << "sc: " << sc.transpose() << endl
        << "ka: " << ka << endl
        << "kd: " << kd << endl
        << "ks: " << ks << endl
        << "pc: " << pc << endl;
}

ostream &operator<<(ostream &out, const Geometry &geometry)
{
    geometry.print(out);
	return out; 
}

Geometry::~Geometry(){}
// geometry should have a hit function that takes in a ray, do the intersection algorithm and have it return bool 
// and at what distance

Sphere::Sphere(json& j) : Geometry(j) {
    radius = j.value("radius", 0);
    centre = parseVector(j, "centre");
}

void Sphere::print(ostream& out) const{
    out << "Sphere: " << endl
        << "radius: " << radius << endl
        << "centre: " << centre.transpose() << endl;
    Geometry::print(out);
}

Rectangle::Rectangle(json& j) : Geometry(j){
    p1 = parseVector(j, "p1");
    p2 = parseVector(j, "p2");
    p3 = parseVector(j, "p3");
    p4 = parseVector(j, "p4");
}

void Rectangle::print(ostream& out) const {
    out << "Rectangle: " << endl
        << "p1: " << p1.transpose() << endl
        << "p2: " << p2.transpose() << endl
        << "p3: " << p3.transpose() << endl
        << "p4: " << p4.transpose() << endl;
    Geometry::print(out);
}
