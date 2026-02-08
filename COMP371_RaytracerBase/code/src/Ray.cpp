#include "Ray.h"

#include <Eigen/Dense>

Ray::Ray(const Eigen::Vector3f& origin, const Eigen::Vector3f direction) : origin(origin), direction(direction){};

// P(t) = O + t*D
// t is a scalar, where along the ray vector we are 
Eigen::Vector3f Ray::at(double t) const {
    return origin + t * direction;
}