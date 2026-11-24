#include <cmath>

#include "matrix.hpp"

// Функция задания единичной матрицы
Matrix4x4 identityMatrix() {
    return {{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
}

// Оператор умножения для удобной записи композиций преобразований
Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b) {
    Matrix4x4 res;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            double sum = 0;
            for (int k = 0; k < 4; ++k) {
                sum += a.m[i][k] * b.m[k][j];
            }
            res.m[i][j] = sum;
        }
    }
    return res;
}

// Функция переноса точки на вектор
Point3D transformPoint(const Matrix4x4& matrix, const Point3D& point) {
    double x = point.x;
    double y = point.y;
    double z = point.z;

    return {
        x * matrix.m[0][0] + y * matrix.m[0][1] + z * matrix.m[0][2] + matrix.m[0][3],
        x * matrix.m[1][0] + y * matrix.m[1][1] + z * matrix.m[1][2] + matrix.m[1][3],
        x * matrix.m[2][0] + y * matrix.m[2][1] + z * matrix.m[2][2] + matrix.m[2][3]
    };
}

// Функция задания матрицы переноса
Matrix4x4 translationMatrix(double dx, double dy, double dz) {
    return {{
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1}
    }};
}

// Функция задания матрицы поворота вокруг Ox для заданного угла 
Matrix4x4 rotationX(double angle) {
    double cos = std::cos(angle);
    double sin = std::sin(angle);

    return {{
        {1,   0,    0, 0},
        {0, cos, -sin, 0},
        {0, sin,  cos, 0},
        {0,   0,    0, 1}
     }};
}

// Функция задания матрицы поворота вокруг Oy для заданного угла 
Matrix4x4 rotationY(double angle) {
    double cos = std::cos(angle);
    double sin = std::sin(angle);

    return {{
        { cos, 0, sin, 0},
        {   0, 1,   0, 0},
        {-sin, 0, cos, 0},
        {   0, 0,   0, 1}
    }};
}

// Функция задания матрицы отражения относительно плоскости Oxy
Matrix4x4 reflectionXY() {
    return {{
        {1, 0,  0, 0},
        {0, 1,  0, 0},
        {0, 0, -1, 0},
        {0, 0,  0, 1}
    }};
}
