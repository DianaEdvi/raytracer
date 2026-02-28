#include "Light.h"

#include "Utility.h"
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
        n = 1;
    }
    else {
        n = j["n"].get<unsigned int>();
    }

    usecenter = j.value("usecenter", false);
    use = j.value("use", true);
}

void Light::print(ostream& out) const {
    out << "id: " << id.transpose() << endl
        << "is: " << is.transpose() << endl
        << "transformMatrix: \n" << transformMatrix << endl
        << "n: " << n << endl
        << "usecenter: " << (usecenter ? "true" : "false") << endl
        << "use: " << (use ? "true" : "false") << endl;
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
    out << "Point: " << endl
        << "centre: " << centre.transpose() << endl;
    Light::print(out);
}

const std::vector<Eigen::Vector3f>& Point::getSamplePoints() const {
    static std::vector<Eigen::Vector3f> samplePoints;
    // samplePoints.clear();
    samplePoints.push_back(centre);
    return samplePoints;
}


Area::Area(json& j) : Light(j){
    p1 = parseVector(j, "p1");
    p2 = parseVector(j, "p2");
    p3 = parseVector(j, "p3");
    p4 = parseVector(j, "p4");
    centre = (p1 + p2 + p3 + p4)/4.0;
}

void Area::print(ostream& out) const {
    out << "Area: " << endl
        << "p1: " << p1.transpose() << endl
        << "p2: " << p2.transpose() << endl
        << "p3: " << p3.transpose() << endl
        << "p4: " << p4.transpose() << endl;
    Light::print(out);
}

const std::vector<Eigen::Vector3f>& Area::getSamplePoints() const {
    std::vector<Eigen::Vector3f> samples;

    if (n <= 0 || usecenter){
        samples.push_back(centre);
        return samples;
    }
    // Create two vectors that represent the edges of the area light
    Eigen::Vector3f u = p1 - p2;
    Eigen::Vector3f v = p3 - p4;

    // Generate n x n sample points on the area light
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            // Find random values from 0 to 1
            float randomU = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            float randomV = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

            // Calculate the sample point using the random values and the edge vectors
            float fractionU = (i + randomU) / static_cast<float>(n);
            float fractionV = (j + randomV) / static_cast<float>(n);
            Eigen::Vector3f samplePoint = p1 + fractionU * u + fractionV * v;
            samples.push_back(samplePoint);
        }
    }
    return samples;
}

