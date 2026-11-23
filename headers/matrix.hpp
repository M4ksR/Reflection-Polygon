#pragma once

#include "structs.hpp"

struct Matrix4x4 {
    double m[4][4];
};

Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b);

Matrix4x4 identityMatrix();

Point3D transformPoint(const Matrix4x4& matrix, const Point3D& point);

Matrix4x4 translationMatrix(double dx, double dy, double dz);

Matrix4x4 rotationX(double angle);

Matrix4x4 rotationY(double angle);

Matrix4x4 reflectionXY();
