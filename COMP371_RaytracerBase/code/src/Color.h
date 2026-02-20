#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <Eigen/Dense>

struct Color {
    float r, g, b;
    // Pastel pink default
    Color(float r = 1.0f, float g = 0.7f, float b = 0.8f) : r(r), g(g), b(b) {}
    Color(Eigen::Vector3f vec) : r(vec.x()), g(vec.y()), b(vec.z()) {}
};

inline std::ostream& operator<<(std::ostream& out, const Color& color) {
    out << color.r << "," << color.g << "," << color.b;
    return out;
}
#endif