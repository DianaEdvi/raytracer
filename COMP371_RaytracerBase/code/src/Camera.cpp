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
    up = up.normalized();
    lookat = lookat.normalized();
    forward = lookat;
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
    float theta = fov * M_PI / 180.0f;        // vertical FOV in radians
    float halfHeight = tan(theta / 2.0f);     // half of view plane height
    float halfWidth = aspect * halfHeight;    // half of view plane width

    // Center of the view plane at distance 1 along forward
    Eigen::Vector3f screenCenter = centre + forward;

    // Top-left corner of the view plane
    Eigen::Vector3f topLeft = screenCenter + halfHeight * camUp - halfWidth * right;

    // Fractional offsets across the view plane for this pixel
    float u = (j + 0.5f) / float(width);   // horizontal fraction
    float v = (i + 0.5f) / float(height);  // vertical fraction (from top)

    // Compute pixel position
    Eigen::Vector3f pixelPos = topLeft 
                             + u * 2.0f * halfWidth * right    // move right
                             - v * 2.0f * halfHeight * camUp; // move down
                             

    // Ray direction
    Eigen::Vector3f dir = (pixelPos - centre).normalized();

    return Ray(centre, dir);
}



