#ifndef JSON_UTILITY_H
#define JSON_UTILITY_H

#include "json.hpp"

#include <Eigen/Dense>

using namespace std;
using namespace nlohmann;

bool parse_geometry(json& j);
Eigen::Vector3f parseVector(const json& jsonObj, const string& propertyName);

#endif