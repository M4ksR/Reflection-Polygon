#include "projection.hpp"

// Функция вычисления координат точки на плоскости проекции
Point2D projectPoint(const Point3D& point, double zPr, double zVp) {
    double t = (zPr - zVp) / (zPr - point.z);
    return {t * point.x, t * point.y};
}

// Функция вычисления координат всех точек многоугольника на плоскости проекции
std::vector<Point2D> projectPolygon(const std::vector<Point3D>& polygon, double zPr, double zVp) {
    std::vector<Point2D> points;
    points.reserve(polygon.size());

    // Для каждой точки применяем projectPoint()
    for (const auto& point : polygon) {
        Point2D p = projectPoint(point, zPr, zVp);
        points.push_back(p);
    }

    return points;
}
