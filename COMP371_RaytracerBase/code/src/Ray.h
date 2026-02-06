#ifndef RAY_H
#define RAY_H
#include <Eigen/Dense>


struct Ray {
    Eigen::Vector3f origin;
    Eigen::Vector3f direction;
};


#endif