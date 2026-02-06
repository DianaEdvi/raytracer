#ifndef RAY_H
#define RAY_H
#include <Eigen/Dense>


class Ray {
    public:
        Ray(){};
        Ray(const Eigen::Vector3f& origin, const Eigen::Vector3f direction);
        const Eigen::Vector3f getOrigin() const {return origin;}
        const Eigen::Vector3f getDirection() const {return direction;}
        Eigen::Vector3f at(double t) const;
    private:
        Eigen::Vector3f origin;
        Eigen::Vector3f direction;
};


#endif