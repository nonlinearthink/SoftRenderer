#pragma once

#include <cmath>
#include <cstddef>

#include "renderbase/math/vec.hpp"

namespace RenderBase {
class Matrix {
public:
    Matrix();
    ~Matrix() {}

    static Matrix Identity();

    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;
    Matrix operator*(float k) const;
    Matrix operator/(float k) const;
    bool operator==(const Matrix& rhs) const;

    Matrix transpose() const;
    Vector3f multiplyVector(const Vector3f& vec) const;

private:
    float _m[16];
};

}  // namespace RenderBase