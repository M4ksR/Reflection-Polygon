#include <cmath>

#include "matrix.hpp"
#include "reflection.hpp"

// Функция нахождения точки на плоскости
Point3D findPointOnPlane(const Plane& plane) {
    // Случай когда коэффициент при Z не равен 0
    if (plane.C != 0) {
        return {0, 0, - plane.D / plane.C};
    }
    
    // Случай когда коэффициент при B не равен 0
    if (plane.B != 0) {
        return {0, - plane.D / plane.B, 0};
    }

    // Случай когда коэффициент при A не равен 0
    return {- plane.D / plane.A, 0, 0};
}

// Функция отражения многоугольника относительно заданной плоскости
std::vector<Point3D> reflectPolygon(const std::vector<Point3D>& polygon, const Plane& plane) {
    // Находим точку на плоскости
    Point3D p0 = findPointOnPlane(plane);

    // Находим матрицы T и T⁻¹
    Matrix4x4 T = translationMatrix(-p0.x, -p0.y, -p0.z);
    Matrix4x4 reverseT = translationMatrix(p0.x, p0.y, p0.z);

    // Вычисляем углы поворотов α и β
    double alpha = (plane.B == 0 && plane.C == 0) ? 0 : std::atan2(plane.B, plane.C);
    double beta = - std::atan2(plane.A, std::sqrt(plane.B * plane.B + plane.C * plane.C));

    // Находим матрицы Rx(α) и Rx(α)⁻¹
    Matrix4x4 Rx = rotationX(alpha);
    Matrix4x4 reverseRx = rotationX(- alpha);

    // Находим матрицы Ry(β) и Ry(β)⁻¹
    Matrix4x4 Ry = rotationY(beta);
    Matrix4x4 reverseRy = rotationY(- beta);

    // Находим матрицу Sxy
    Matrix4x4 S = reflectionXY();

    // Вычисляем финальную матрицу преобразования
    Matrix4x4 M = reverseT * reverseRx * reverseRy * S * Ry * Rx * T;

    std::vector<Point3D> reflected;
    reflected.reserve(polygon.size());

    // Применяем ее для каждой точки
    for (const auto& point : polygon) {
        Point3D p = transformPoint(M, point);
        reflected.push_back(p);
    }

    return reflected;
}
