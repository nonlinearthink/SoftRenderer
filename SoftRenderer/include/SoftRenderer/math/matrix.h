#pragma once

#include <cmath>
#include <cstddef>

#include "SoftRenderer/math/vec.hpp"

namespace SoftRenderer {
class Matrix {
public:
    float m[4][4];

    Matrix() : m{} {};
    Matrix(float _m[4][4]);
    ~Matrix() {}

    static Matrix Identity();

    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;
    Matrix operator*(float k) const;
    Matrix operator/(float k) const;
    bool operator==(const Matrix& rhs) const;

    Matrix Transpose() const;
    Vector3f MultiplyVector(const Vector3f& vec) const;
};
}  // namespace SoftRenderer