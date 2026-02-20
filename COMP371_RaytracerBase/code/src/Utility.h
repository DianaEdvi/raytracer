#ifndef JSON_UTILITY_H
#define JSON_UTILITY_H

#include "json.hpp"

#include <Eigen/Dense>
#include <Eigen/Core>

using namespace std;
using namespace nlohmann;

bool parse_geometry(json& j);
bool parse_lights(json& j);
bool parse_output(json& j);

bool containsMandatoryProperty(const json& jsonObj, const string& property);

Eigen::Vector3f parseVector(const json& jsonObj, const string& propertyName);
float parseFloat(const json& jsonObj, const string& propertyName);
Eigen::Matrix4f parseMatrix4f(const json& jsonObj, const string& propertyName);
bool parseBool(const json& jsonObj, const string& propertyName);
Eigen::Vector3i parseRaysPerPixel(const json& jsonObj, const string& propertyName);
int save_new_ppm(string file_name, const vector<double>& buffer, int dimx, int dimy);
#endif