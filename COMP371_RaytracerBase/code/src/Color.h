#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <Eigen/Dense>

struct Color {
    float r, g, b;
    Color(float r = 0.0f, float g = 0.0f, float b = 0.0f) : r(r), g(g), b(b) {}
    Color(Eigen::Vector3f vec) : r(vec.x()), g(vec.y()), b(vec.z()) {}
};

inline std::ostream& operator<<(std::ostream& out, const Color& color) {
    out << color.r << "," << color.g << "," << color.b;
    return out;
}

inline Color operator+(const Color& A, const Color& B) {
    return Color(A.r + B.r, A.g + B.g, A.b + B.b);
}

inline Color operator/(const Color& A, float scalar) {
    if (scalar == 0.0f) return A; 
    return Color(A.r / scalar, A.g / scalar, A.b / scalar);
}
#endif