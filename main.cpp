#include <algorithm>
#include <iostream>

#include "bmp.hpp"
#include "clipping.hpp"
#include "matrix.hpp"
#include "projection.hpp"
#include "reflection.hpp"
#include "structs.hpp"

int main() {
    // Задаем размер изображения
    int WIDTH;
    int HEIGHT;
    std::cout << "Enter image size: WIDTH HEIGHT" << std::endl;
    std::cin >> WIDTH >> HEIGHT;

    // Создаем вектор размера HEIGHT x WIDTH для пикселей
    std::vector<std::vector<RGB>> Image(HEIGHT, std::vector<RGB>(WIDTH, {255,255,255}));

    // Задаем количество вершин
    int VertexCount;
    std::cout << "Enter vertex count: VertexCount" << std::endl;
    std::cin >> VertexCount;

    std::vector<Point3D> points;
    points.reserve(VertexCount);

    // Задаем все вершины
    for (int i = 1; i <= VertexCount; ++i) {
        double x, y, z;
        std::cout << "Enter vertex number " << i << ": x y z" << std::endl;
        std::cin >> x >> y >> z;
        points.push_back(Point3D{x,y,z});
    }

    // Задаем плоскость
    Plane plane;
    std::cout << "Enter coefficients (Ax + By + Cz + D = 0): A B C D" << std::endl;
    std::cin >> plane.A >> plane.B >> plane.C >> plane.D;

    // ...
    std::vector<Point3D> reflected = reflectPolygon(points, plane);

    double maxZ = 0;

    auto findMax = [&maxZ](const Point3D& p) {
        maxZ = std::max(maxZ, p.z);
    };

    std::for_each(points.begin(), points.end(), findMax);
    std::for_each(reflected.begin(), reflected.end(), findMax);

    double zPr = maxZ + 10;
    double zVp = maxZ + 5;

    std::vector<Point2D> projectedOriginal = projectPolygon(points, zPr, zVp);
    std::vector<Point2D> projectedReflected = projectPolygon(reflected, zPr, zVp);
    
    double halfWidth = 10;
    double halfHeight = halfWidth * HEIGHT / WIDTH;

    ClipRect rect = {-halfWidth, -halfHeight, halfWidth, halfHeight};

    std::vector<Point2D> clippedOriginal = clipPolygon(projectedOriginal, rect);
    std::vector<Point2D> clippedReflected = clipPolygon(projectedReflected, rect);

    std::vector<PixelPoint> screenOriginal;
    screenOriginal.reserve(clippedOriginal.size());
    for (const auto& point : clippedOriginal) {
        PixelPoint p = toScreen(point, rect, WIDTH, HEIGHT);
        screenOriginal.push_back(p);
    }

    std::vector<PixelPoint> screenReflected;
    screenReflected.reserve(clippedReflected.size());
        for (const auto& point : clippedReflected) {
        PixelPoint p = toScreen(point, rect, WIDTH, HEIGHT);
        screenReflected.push_back(p);
    }

    RGB blue = {255, 0, 0};
    RGB red = {0, 0, 255};
    
    if (screenOriginal.size() >= 2) { 
        drawPolygon(Image, screenOriginal, blue);
    }

    if (screenReflected.size() >= 2) {
        drawPolygon(Image, screenReflected, red);
    }

    saveBMP(Image, "result.bmp");
    
    return 0;
}
