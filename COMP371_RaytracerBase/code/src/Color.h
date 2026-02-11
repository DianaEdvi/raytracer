#ifndef COLOR_H
#define COLOR_H

#include <iostream>

struct Color {
    float r, g, b;
    // Pastel pink default
    Color(float r = 1.0f, float g = 0.7f, float b = 0.8f) : r(r), g(g), b(b) {}

};

inline std::ostream& operator<<(std::ostream& out, const Color& color) {
    out << color.r << "," << color.g << "," << color.b;
    return out;
}
#endif