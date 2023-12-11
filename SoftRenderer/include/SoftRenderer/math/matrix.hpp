#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>

#include "SoftRenderer/math/common.h"
#include "SoftRenderer/math/vec.hpp"

namespace SoftRenderer {
template <size_t N>
class Matrix {
public:
    float m[N][N];

    Matrix();
    Matrix(float _m[N][N]);
    ~Matrix() {}

    static Matrix<N> Identity();

    Matrix<N> operator+(const Matrix<N>& rhs) const;
    Matrix<N> operator-(const Matrix<N>& rhs) const;
    Matrix<N> operator*(const Matrix<N>& rhs) const;
    Matrix<N> operator*(float k) const;
    Matrix<N> operator/(float k) const;
    bool operator==(const Matrix<N>& rhs) const;

    Matrix<N> Transpose() const;
    inline float Determinant() const;
    Matrix<N> Inverse() const;
};

template <size_t N>
Matrix<N>::Matrix() : m{} {}

template <size_t N>
Matrix<N>::Matrix(float _m[N][N]) {
    std::copy(&_m[0][0], &_m[N - 1][N - 1] + 1, &m[0][0]);
}

template <size_t N>
Matrix<N> Matrix<N>::Identity() {
    float identity[N][N] = {0};
    for (size_t i = 0; i < N; ++i) {
        identity[i][i] = 1.0f;
    }
    return Matrix<N>(identity);
}

template <size_t N>
Matrix<N> Matrix<N>::operator+(const Matrix<N>& rhs) const {
    Matrix<N> result;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result.m[i][j] = m[i][j] + rhs.m[i][j];
        }
    }
    return result;
}

template <size_t N>
Matrix<N> Matrix<N>::operator-(const Matrix<N>& rhs) const {
    Matrix<N> result;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result.m[i][j] = m[i][j] - rhs.m[i][j];
        }
    }
    return result;
}

template <size_t N>
Matrix<N> Matrix<N>::operator*(const Matrix<N>& rhs) const {
    Matrix<N> result;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            for (size_t k = 0; k < N; ++k) {
                result.m[i][j] += m[i][k] * rhs.m[k][j];
            }
        }
    }
    return result;
}

template <size_t N>
Matrix<N> Matrix<N>::operator*(float k) const {
    Matrix<N> result;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result.m[i][j] = m[i][j] * k;
        }
    }
    return result;
}

template <size_t N>
Matrix<N> Matrix<N>::operator/(float k) const {
    Matrix<N> result;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result.m[i][j] = m[i][j] / k;
        }
    }
    return result;
}

template <size_t N>
bool Matrix<N>::operator==(const Matrix<N>& rhs) const {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (!Equals(m[i][j], rhs.m[i][j])) {
                return false;
            }
        }
    }
    return true;
}

template <size_t N>
Matrix<N> Matrix<N>::Transpose() const {
    Matrix<N> result;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result.m[j][i] = m[i][j];
        }
    }
    return result;
}

template <>
inline float Matrix<2>::Determinant() const {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

template <size_t N>
inline float Matrix<N>::Determinant() const {
    Matrix<N - 1> sub_matrix;
    float det = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 1; j < N; j++) {
            int col = 0;
            for (int k = 0; k < N; k++) {
                if (j != k) {
                    sub_matrix.m[j - 1][col++] = m[j][k];
                }
            }
        }
        float sign = (i & 1) ? -1 : 1;
        det += sign * m[0][i] * sub_matrix.Determinant();
    }
    return det;
}

// Vector3f Matrix::MultiplyVector(const Vector3f& vec) const {
//     float x = m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z;
//     float y = m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z;
//     float z = m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z;
//     Vector3f result(x, y, z);
//     return result;
// }

using Matrix2 = Matrix<2>;
using Matrix3 = Matrix<3>;
using Matrix4 = Matrix<4>;
}  // namespace SoftRenderer
