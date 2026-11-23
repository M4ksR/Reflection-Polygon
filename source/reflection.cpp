#include <cmath>

#include "matrix.hpp"
#include "reflection.hpp"

Point3D findPointOnPlane(const Plane& plane) {
    if (plane.C != 0) {
        return {0, 0, - plane.D / plane.C};
    }
    
    if (plane.B != 0) {
        return {0, - plane.D / plane.B, 0};
    }

    return {- plane.D / plane.A, 0, 0};
}

std::vector<Point3D> reflectPolygon(const std::vector<Point3D>& polygon, const Plane& plane) {
    Point3D p0 = findPointOnPlane(plane);

    Matrix4x4 T = translationMatrix(-p0.x, -p0.y, -p0.z);
    Matrix4x4 reverseT = translationMatrix(p0.x, p0.y, p0.z);

    double alpha = (plane.B == 0 && plane.C == 0) ? 0 : std::atan2(plane.B, plane.C);
    double beta = - std::atan2(plane.A, std::sqrt(plane.B * plane.B + plane.C * plane.C));

    Matrix4x4 Rx = rotationX(alpha);
    Matrix4x4 reverseRx = rotationX(- alpha);

    Matrix4x4 Ry = rotationY(beta);
    Matrix4x4 reverseRy = rotationY(- beta);

    Matrix4x4 S = reflectionXY();

    Matrix4x4 M = reverseT * reverseRx * reverseRy * S * Ry * Rx * T;

    std::vector<Point3D> reflected;
    reflected.reserve(polygon.size());

    for (const auto& point : polygon) {
        Point3D p = transformPoint(M, point);
        reflected.push_back(p);
    }

    return reflected;
}
