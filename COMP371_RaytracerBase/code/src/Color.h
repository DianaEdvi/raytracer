#ifndef COLOR_H
#define COLOR_H

struct Color {
    float r, g, b;
    // Pastel pink default
    Color(float r = 1.0f, float g = 0.7f, float b = 0.8f) : r(r), g(g), b(b) {}

};
#endif