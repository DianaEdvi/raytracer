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
    z = (lookat - centre).normalized();
    x = up.cross(z).normalized();
    y = z.cross(x);
}


ostream &operator<<(ostream &out, const Camera &camera){
    out << "Lookat: " << camera.lookat.transpose() << endl;
    out << "Up: " << camera.up.transpose() << endl;
    out << "FOV: " << camera.fov << endl;
    out << "Camera centre: " << camera.centre.transpose() << endl;
    out << "width: " << camera.width << endl;
    out << "height: " << camera.height << endl;
    out << "z: " << camera.z.transpose() << endl;
    out << "x: " << camera.x.transpose() << endl;
    out << "y: " << camera.y.transpose() << endl;

    return out;
}

// Calculate a ray that goes through a pixel on the screen
Ray Camera::getRay(unsigned int i, unsigned int j) const {
    float aspect = float(width) / float(height);
    float theta = fov * M_PI / 180.0f;
    float halfHeight = tan(theta / 2.0f);

    float deltaX = (2 * aspect * halfHeight) / float(width);
    float deltaY = (2 * halfHeight) / float(height);

    Eigen::Vector3f A = centre + z;
    Eigen::Vector3f B = A + halfHeight * y;
    Eigen::Vector3f C = B - aspect * halfHeight * x;

    Eigen::Vector3f pixelPos = C + (j + 0.5f) * deltaX * x - (i + 0.5f) * deltaY * y;
    Eigen::Vector3f dir = (pixelPos - centre).normalized();

    return Ray(centre, dir);
}


