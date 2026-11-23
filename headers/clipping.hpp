#pragma once

#include <vector>

#include "structs.hpp"

enum class ClipEdge {Left, Right, Bottom, Top};

struct ClipRect {
    double xmin;
    double ymin;
    double xmax;
    double ymax;
};

bool isInside(const Point2D& point, const ClipRect& rect, ClipEdge edge);

std::vector<Point2D> clipPolygon(const std::vector<Point2D>& polygon, const ClipRect& rect);
