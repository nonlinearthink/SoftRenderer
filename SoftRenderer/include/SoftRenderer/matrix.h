#pragma once

#include <cassert>

#include "SoftRenderer/common.h"

namespace SoftRenderer {
// Matrix Template Class
template <size_t N>
class Matrix {
    // Matrix<1> is meanningless.
    static_assert(N > 1, "Size of the matrix must be greater than 1");

public:
    // Matrix data
    float m[N][N]{};

    Matrix() = default;
    // Constructor for uniform initialization
    Matrix(const std::initializer_list<float>& list);

    // Get an identity matrix
    static Matrix<N> Identity();

    Matrix<N> operator+(const Matrix<N>& rhs) const;
    Matrix<N> operator-(const Matrix<N>& rhs) const;
    Matrix<N> operator*(const Matrix<N>& rhs) const;
    Matrix<N> operator*(float k) const;
    Matrix<N> operator/(float k) const;
    bool operator==(const Matrix<N>& rhs) const;

    // Get the transpose matrix
    [[nodiscard]] Matrix<N> Transpose() const;
    // Compute the cofactor of matrix, more details:
    // https://en.wikipedia.org/wiki/Minor_(linear_algebra)#Applications_of_minors_and_cofactors
    [[nodiscard]] float Cofactor(size_t row, size_t col) const;
    // Compute the determinant of matrix, more details:
    // https://en.wikipedia.org/wiki/Determinant#Definition
    [[nodiscard]] float Determinant() const;
    // Compute the adjoint matrix, more details:
    // https://en.wikipedia.org/wiki/Adjugate_matrix#Definition
    [[nodiscard]] Matrix<N> Adjoint() const;
    // Compute the inverse matrix, return std::nullopt if there's no inverse
    // matrix, otherwise return a matrix wrapped by a optional
    [[nodiscard]] Matrix<N> Invert() const;
};

#pragma region Matrix Template Implementation

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
    return {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
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
            if (!MathUtils::Equals(m[i][j], rhs.m[i][j])) {
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
    // Prevents the template class from continuing to create Matrix<1>'s
    // Cofactor function
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
    // Accelerating the computation of the determinant of Matrix2
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

template <>
inline float Matrix<3>::Determinant() const {
    // Accelerating the computation of the determinant of Matrix3
    return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
           m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
           m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

template <size_t N>
float Matrix<N>::Determinant() const {
    // Use cofactor expansions to compute determinant, expand the first row of
    // the matrix.
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
Matrix<N> Matrix<N>::Invert() const {
    /// Use adjoint matrix and determinant to compute the inverse matrix.
    float det = Determinant();
    if (det == 0) {
        return *this;
    }
    Matrix<N> result;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result.m[j][i] = Cofactor(i, j) / det;
        }
    }
    return result;
}

#pragma endregion Matrix Template Implementation

using Matrix2 = Matrix<2>;
using Matrix3 = Matrix<3>;
using Matrix4 = Matrix<4>;
}  // namespace SoftRenderer
