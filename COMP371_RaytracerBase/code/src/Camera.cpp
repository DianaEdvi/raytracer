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
    w = (lookat - centre).normalized();
    u = up.cross(w).normalized();
    v = w.cross(u);
}


ostream &operator<<(ostream &out, const Camera &camera){
    out << "Lookat: " << camera.lookat.transpose() << endl;
    out << "Up: " << camera.up.transpose() << endl;
    out << "FOV: " << camera.fov << endl;
    out << "Camera centre: " << camera.centre.transpose() << endl;
    out << "width: " << camera.width << endl;
    out << "height: " << camera.height << endl;
    out << "w: " << camera.w.transpose() << endl;
    out << "u: " << camera.u.transpose() << endl;
    out << "v: " << camera.v.transpose() << endl;

    return out;
}
 

