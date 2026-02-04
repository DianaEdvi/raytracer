#include "Light.h"

#include "jsonUtility.h"
#include "json.hpp"

#include <iostream>

using namespace nlohmann;
using namespace std;

unique_ptr<Light> LightFactory::create(json& j) {
    string type = j["type"].get<string>();

    if (type == "point"){
        return make_unique<Point>(j);
    }
    else if (type == "area"){
        return make_unique<Area>(j);
    }    

    throw runtime_error("Unknown light type: " + type);
}

Light::Light(json& j){
    id = parseVector(j, "id");
    is = parseVector(j, "is");
    transformMatrix = parseMatrix4f(j, "transform");

    if (!j.contains("n")){
        // cout << "n does not exist, but no matter! Setting it as 0" << endl;
        n = 0;
    }
    else {
        n = j["n"].get<unsigned int>();
    }

    usecenter = j.value("usecenter", false);
    use = j.value("use", true);
}

void Light::print(ostream& out) const {
	   out << "id: \n" << id << "\n"
            << "is: \n" << is << "\n"
            << "transformMatrix: \n" << transformMatrix << "\n"
            << "n: " << n << "\n"
            << "usecenter: " << boolalpha << usecenter << "\n"
            << "use: " << boolalpha << use << "\n";
}

ostream &operator<<(ostream &out, const Light &light)
{
    light.print(out);
	return out; 
}

Light::~Light(){}

Point::Point(json& j) : Light(j) {
    centre = parseVector(j, "centre");
}

void Point::print(ostream& out) const{
    out << "centre: \n" << centre << "\n";
    Light::print(out);
}

Area::Area(json& j) : Light(j){
    p1 = parseVector(j, "p1");
    p2 = parseVector(j, "p2");
    p3 = parseVector(j, "p3");
    p4 = parseVector(j, "p4");
}

void Area::print(ostream& out) const {
    out << "p1: \n" << p1 << "\n"
    << "p2: \n" << p2 << "\n"
    << "p3: \n" << p3 << "\n"
    << "p4: \n" << p4 << "\n";
    Light::print(out);
}
