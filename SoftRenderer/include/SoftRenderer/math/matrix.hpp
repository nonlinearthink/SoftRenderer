#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <optional>

#include "SoftRenderer/math/common.h"
#include "SoftRenderer/math/vec.hpp"

namespace SoftRenderer {
/**
 * @brief Template matrix class
 * @tparam N Dimension of matrix
 */
template <size_t N>
class Matrix {
    static_assert(N > 1, "Size of the matrix must be greater than 1");

public:
    float m[N][N];  /// Matrix data

    Matrix() : m{} {};
    /**
     * @brief Constructor for uniform initialization
     * @param list A float initializer list, e.g. {1.0, 2.0, 3.0, 4.0}
     */
    explicit Matrix(const std::initializer_list<float>& list);
    ~Matrix() = default;

    /**
     * @brief Get an identity matrix
     */
    static Matrix<N> Identity();

    Matrix<N> operator+(const Matrix<N>& rhs) const;
    Matrix<N> operator-(const Matrix<N>& rhs) const;
    Matrix<N> operator*(const Matrix<N>& rhs) const;
    Matrix<N> operator*(float k) const;
    Matrix<N> operator/(float k) const;
    bool operator==(const Matrix<N>& rhs) const;

    /**
     * @brief Get the transpose matrix
     * @return A matrix has the same dimension
     */
    Matrix<N> Transpose() const;
    /**
     * @brief Compute the cofactor of matrix
     * @see
     * https://en.wikipedia.org/wiki/Minor_(linear_algebra)#Applications_of_minors_and_cofactors
     * @param row The cofactor expansion row
     * @param col The cofactor expansion col
     * @return A float cofactor value with a sign
     */
    float Cofactor(size_t row, size_t col) const;
    /**
     * @brief Compute the determinant of matrix
     * @see https://en.wikipedia.org/wiki/Determinant#Definition
     * @return A float matrix determinant value
     */
    float Determinant() const;
    /**
     * @brief Compute the adjoint matrix
     * @see https://en.wikipedia.org/wiki/Adjugate_matrix#Definition
     * @return A matrix has the same dimension
     */
    Matrix<N> Adjoint() const;
    /**
     * @brief Compute the inverse matrix
     * @return a optional matrix has the same dimension
     *  @retval return std::nullopt if there's no inverse matrix, otherwise
     * return a matrix wrapped by a optional
     */
    std::optional<Matrix<N>> Inverse() const;
};

template <size_t N>
Matrix<N>::Matrix(const std::initializer_list<float>& list) {
    if (list.size() <= N * N) {
        std::copy(list.begin(), list.end(), &m[0][0]);
    } else {
        std::copy(list.begin(), list.begin() + N * N, &m[0][0]);
    }
}

template <size_t N>
Matrix<N> Matrix<N>::Identity() {
    Matrix<N> result;
    for (size_t i = 0; i < N; ++i) {
        result.m[i][i] = 1.0f;
    }
    return result;
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
    /**
     * Prevents the template class from continuing to create Matrix<1>'s
     * Cofactor function
     */
    assert(row < 2 && col < 2);
    float sign = ((row + col) & 1) ? -1 : 1;
    return sign * m[1 - row][1 - col];
}

template <size_t N>
float Matrix<N>::Cofactor(size_t row, size_t col) const {
    Matrix<N - 1> minor;
    int ti = 0;
    int tj = 0;
    for (int i = 0; i < N; i++) {
        if (i == row) {
            continue;
        }
        tj = 0;
        for (int j = 0; j < N; j++) {
            if (j == col) {
                continue;
            }
            minor.m[ti][tj] = m[i][j];
            tj++;
        }
        ti++;
    }
    float sign = ((row + col) & 1) ? -1 : 1;
    return sign * m[row][col] * minor.Determinant();
}

template <>
inline float Matrix<2>::Determinant() const {
    /// Accelerating the computation of the determinant of Matrix2
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

template <>
inline float Matrix<3>::Determinant() const {
    /// Accelerating the computation of the determinant of Matrix3
    return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
           m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
           m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

template <size_t N>
float Matrix<N>::Determinant() const {
    /**
     * Use cofactor expansions to compute determinant, expand the first row of
     * the matrix.
     */
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
            result.m[j][i] = Cofactor(i, j);
        }
    }
    return result;
}

template <size_t N>
std::optional<Matrix<N>> Matrix<N>::Inverse() const {
    /// Use adjoint matrix and determinant to compute the inverse matrix
    std::optional<Matrix<N>> result;
    float det = Determinant();
    if (det == 0) {
        return result;
    }
    Matrix<N> result_mat;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result_mat.m[j][i] = Cofactor(i, j) / det;
        }
    }
    result.emplace(result_mat);
    return result;
}

// Vector3f TransformVector(const Vector3f& vec, const Matrix4& mat) {
//     float x = mat.m[0][0] * vec.x + mat.m[0][1] * vec.y + mat.m[0][2] *
//     vec.z; float y = mat.m[1][0] * vec.x + mat.m[1][1] * vec.y + mat.m[1][2]
//     * vec.z; float z = mat.m[2][0] * vec.x + mat.m[2][1] * vec.y +
//     mat.m[2][2] * vec.z; Vector3f result(x, y, z); return result;
// }

using Matrix2 = Matrix<2>;
using Matrix3 = Matrix<3>;
using Matrix4 = Matrix<4>;
}  // namespace SoftRenderer
