#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <optional>

#include "SoftRenderer/math/common.h"
#include "SoftRenderer/math/vec.hpp"

namespace SoftRenderer {
template <size_t N>
class Matrix {
    static_assert(N > 1, "Size of the matrix must be greater than 1");

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
    float Cofactor(size_t row, size_t col) const;
    float Determinant() const;
    Matrix<N> Adjoint() const;
    std::optional<Matrix<N>> Inverse() const;
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
inline float Matrix<2>::Cofactor(size_t row, size_t col) const {
    assert(row < 2 && col < 2);
    return m[1 - row][1 - col];
}

template <size_t N>
float Matrix<N>::Cofactor(size_t row, size_t col) const {
    Matrix<N - 1> minor;
    int ti = 0;
    int tj = 0;
    for (int i = 0; i < N; i++, ti++) {
        if (i == row) {
            continue;
        }
        tj = 0;
        for (int j = 0; j < N; j++, tj++) {
            if (j == col) {
                continue;
            }
            minor.m[ti][tj] = m[i][j];
        }
    }
    float sign = ((row + col) & 1) ? -1 : 1;
    return sign * m[row][col] * minor.Determinant();
}

/**
 * Accelerating the computation of the determinant of Matrix2
 */
template <>
inline float Matrix<2>::Determinant() const {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

/**
 * Accelerating the computation of the determinant of Matrix3
 */
template <>
inline float Matrix<3>::Determinant() const {
    return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
           m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
           m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

/**
 * Use cofactor expansions to compute determinant, expand the first row of the
 * matrix.
 */
template <size_t N>
float Matrix<N>::Determinant() const {
    float det = 0;
    for (int k = 0; k < N; k++) {
        det += Cofactor(0, k);
    }
    return det;
}

template <size_t N>
Matrix<N> Matrix<N>::Adjoint() const {
    Matrix<N> result;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result.m[i][j] = Cofactor(i, j);
        }
    }
    return result;
}

template <size_t N>
std::optional<Matrix<N>> Matrix<N>::Inverse() const {
    std::optional<Matrix<N>> result;
    float det = Determinant();
    if (det == 0) {
        return result;
    }
    Matrix<N> temp;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp.m[i][j] = Cofactor(i, j) / det;
        }
    }
    result.emplace(temp);
    return result;
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
