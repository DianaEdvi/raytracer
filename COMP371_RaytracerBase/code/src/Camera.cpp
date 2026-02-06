#include "Camera.h"

#include <iostream>
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
}


ostream &operator<<(ostream &out, const Camera &camera){
    out << "Lookat: " << camera.lookat.transpose() << endl;
    out << "Up: " << camera.up.transpose() << endl;
    out << "FOV: " << camera.fov << endl;
    out << "Camera centre: " << camera.centre.transpose() << endl;
    out << "width: " << camera.width << endl;
    out << "height: " << camera.height << endl;
    return out;
}
 

