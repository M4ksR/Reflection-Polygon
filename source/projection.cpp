#include "projection.hpp"

Point2D projectPoint(const Point3D& point, double zPr, double zVp) {
    double k = (zPr - zVp) / (zPr - point.z);
    return {k * point.x, k * point.y};
}

std::vector<Point2D> projectPolygon(const std::vector<Point3D>& polygon, double zPr, double zVp) {
    std::vector<Point2D> points;
    points.reserve(polygon.size());

    for (const auto& point : polygon) {
        Point2D p = projectPoint(point, zPr, zVp);
        points.push_back(p);
    }

    return points;
}
