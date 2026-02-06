#ifndef CAMERA_H
#define CAMERA_H
#include <Eigen/Dense>

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
        Eigen::Vector3f w;
        Eigen::Vector3f u;
        Eigen::Vector3f v;
    public: 
        Camera(Eigen::Vector3f lookat, 
            Eigen::Vector3f up, 
            Eigen::Vector3f centre,
            float fov,
            unsigned int width,
            unsigned int height
        );
        friend ostream &operator<<(ostream &out, const Camera &camera);
};


#endif