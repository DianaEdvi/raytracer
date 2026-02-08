#ifndef CAMERA_H
#define CAMERA_H
#include <Eigen/Dense>

#include "Ray.h"

#include <iostream>
using namespace std;

class Camera {
    private: 
        const Eigen::Vector3f lookat;
        const Eigen::Vector3f up;
        const Eigen::Vector3f centre;
        float fov;
        unsigned int width;
        unsigned int height;
        // basis  vectors
        Eigen::Vector3f z;
        Eigen::Vector3f x;
        Eigen::Vector3f y;
    public: 
        Camera(Eigen::Vector3f lookat, 
            Eigen::Vector3f up, 
            Eigen::Vector3f centre,
            float fov,
            unsigned int width,
            unsigned int height
        );
        Ray getRay(unsigned int i, unsigned int j) const;
        unsigned int getWidth() const { return width; }
        unsigned int getHeight() const { return height; }
        friend ostream &operator<<(ostream &out, const Camera &camera);
};


#endif