#pragma once

#include <vector>

#include "structs.hpp"

Point3D findPointOnPlane(const Plane& plane);

std::vector<Point3D> reflectPolygon(const std::vector<Point3D>& polygon, const Plane& plane);
