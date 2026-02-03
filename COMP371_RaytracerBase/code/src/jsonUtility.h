#ifndef JSON_UTILITY_H
#define JSON_UTILITY_H

#include "json.hpp"

#include <Eigen/Dense>

using namespace std;
using namespace nlohmann;

bool parse_geometry(json& j);
bool parse_lights(json& j);
bool parse_output(json& j);

bool containsMandatoryProperty(const json& jsonObj, const string& property);

Eigen::Vector3f parseVector(const json& jsonObj, const string& propertyName);
float parseFloat(const json& jsonObj, const string& propertyName);

#endif