#include "Camera.h"

#include <iostream>
#include <cmath>

using namespace std;

Camera::Camera(Eigen::Vector3f lookat,
               Eigen::Vector3f up,
               Eigen::Vector3f centre,
               float fov,
               unsigned int width,
               unsigned int height)
    : lookat(lookat),
      up(up),
      centre(centre),
      fov(fov),
      width(width),
      height(height)
{
    forward = (lookat - centre).normalized();
    right = forward.cross(up).normalized();
    camUp = right.cross(forward);
}


ostream &operator<<(ostream &out, const Camera &camera){
    out << "Lookat: " << camera.lookat.transpose() << endl;
    out << "Up: " << camera.up.transpose() << endl;
    out << "FOV: " << camera.fov << endl;
    out << "Camera centre: " << camera.centre.transpose() << endl;
    out << "width: " << camera.width << endl;
    out << "height: " << camera.height << endl;
    out << "forward: " << camera.forward.transpose() << endl;
    out << "right: " << camera.right.transpose() << endl;
    out << "camUp: " << camera.camUp.transpose() << endl;

    return out;
}

// Calculate a ray that goes through a pixel on the screen
Ray Camera::getRay(unsigned int i, unsigned int j) const {
    float aspect = float(width) / float(height);
    float theta = fov * M_PI / 180.0f;
    float halfHeight = tan(theta / 2.0f);

    float deltaX = (2 * aspect * halfHeight) / float(width);
    float deltaY = (2 * halfHeight) / float(height);

    Eigen::Vector3f A = centre + forward;
    Eigen::Vector3f B = A + halfHeight * camUp;
    Eigen::Vector3f C = B - aspect * halfHeight * right;

    Eigen::Vector3f pixelPos = C + (j + 0.5f) * deltaX * right - (i + 0.5f) * deltaY * camUp;
    Eigen::Vector3f dir = (pixelPos - centre).normalized();

    return Ray(centre, dir);
}


