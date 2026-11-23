#pragma once

#include <vector>

#include "structs.hpp"

Point2D projectPoint(const Point3D& point, double zPr, double zVp);

std::vector<Point2D> projectPolygon(const std::vector<Point3D>& polygon, double zPr, double zVp);
