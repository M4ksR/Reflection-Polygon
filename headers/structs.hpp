#pragma once

#include <cstdint>

struct Point3D {
    double x;
    double y;
    double z;
};

struct Point2D {
    double x;
    double y;
};

struct PixelPoint {
    int x;
    int y;
};

struct Plane {
    double A;
    double B;
    double C;
    double D;
};

struct RGB {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};
