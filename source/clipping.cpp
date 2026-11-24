#include <stdexcept>

#include "clipping.hpp"

// Функция проверки нахождения точки внутри границы
bool isInside(const Point2D& point, const ClipRect& rect, ClipEdge edge) {
    switch (edge) {
        // Для левой границы x должен быть >= минимального X границы
        case ClipEdge::Left: 
            return point.x >= rect.xmin;

        // Для правой границы x должен быть <= максимального X границы
        case ClipEdge::Right: 
            return point.x <= rect.xmax;

        // Для нижней границы y должен быть >= минимального Y границы
        case ClipEdge::Bottom: 
            return point.y >= rect.ymin;

        // Для верхней границы y должен быть <= максимального Y границы
        case ClipEdge::Top: 
            return point.y <= rect.ymax;

        default:
            throw std::logic_error("error isInside");
    }
}

// Функция нахождения точки пересечения с границей
Point2D findIntersection(const Point2D& p1, const Point2D& p2, const ClipRect& rect, ClipEdge edge) {
    double x;
    double y;
    double t;
    
    switch (edge) {
        // Пересечение для левой границы
        case ClipEdge::Left:
            t = (rect.xmin - p1.x) / (p2.x - p1.x);
            y = p1.y + t * (p2.y - p1.y);
            return {rect.xmin, y};

        // Пересечение для правой границы
        case ClipEdge::Right:
            t = (rect.xmax - p1.x) / (p2.x - p1.x);
            y = p1.y + t * (p2.y - p1.y);
            return {rect.xmax, y};

        // Пересечение для нижней границы
        case ClipEdge::Bottom:
            t = (rect.ymin - p1.y) / (p2.y - p1.y);
            x = p1.x + t * (p2.x - p1.x);
            return {x, rect.ymin};

        // Пересечение для верхней границы
        case ClipEdge::Top:
            t = (rect.ymax - p1.y) / (p2.y - p1.y);
            x = p1.x + t * (p2.x - p1.x);
            return {x, rect.ymax};

        default:
            throw std::logic_error("error findIntersection");
    }
}

// Функция обрезки многоугольника
std::vector<Point2D> clipPolygon(const std::vector<Point2D>& polygon, const ClipRect& rect) {
    // Берем все точки нашего многоугольника
    std::vector<Point2D> result = polygon;
    std::vector<ClipEdge> edges = {ClipEdge::Left, ClipEdge::Right, ClipEdge::Bottom, ClipEdge::Top};

    // Начинаем перебирать границы в порядке: Левая Правая Нижняя Верхняя
    for (const auto& edge : edges) {
        // В качестве входных данных берем наши собранные точки
        std::vector<Point2D> input = result;
        // Очищаем result чтобы в последствии в него поместить полученные точки
        result.clear();

        // Если точек нет то возвращаем пустой вектор
        if (input.empty()) {
            return result;
        }
        
        // В качестве V1 берем последнюю точку
        Point2D prev = input[input.size() - 1];

        // Начинаем перебирать V2
        for (const auto& curr : input) {
            // Проверяем каждую вершину на нахождение в области
            bool prevInside = isInside(prev, rect, edge);
            bool currInside = isInside(curr, rect, edge);

            // Если обе вершины внутри, то кладем V2
            if (prevInside && currInside) {
                result.push_back(curr);
            }
            // Если внутри только V1, то кладем точку пересечения
            else if (prevInside) {
                Point2D intersection = findIntersection(prev, curr, rect, edge);
                result.push_back(intersection);
            }
            // Если внутри только V2, то кладем точку пересечения и V2
            else if (currInside) {
                Point2D intersection = findIntersection(prev, curr, rect, edge);
                result.push_back(intersection);
                result.push_back(curr);
            }

            // V1 = V2
            prev = curr;
        }
    }

    // Возвращаем вершины отсеченного многоугольника
    return result;
}
