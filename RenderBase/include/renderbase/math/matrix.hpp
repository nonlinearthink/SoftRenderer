#pragma once

#include <cmath>
#include <cstddef>

namespace RenderBase {
template <size_t N>
class Matrix {
   public:
    Matrix<N>();
    ~Matrix<N>() {}

    static Matrix<N> Identity();

    float operator[](size_t n) const;
    Matrix<N> operator+(const Matrix<N>& rhs) const;
    Matrix<N> operator-(const Matrix<N>& rhs) const;
    Matrix<N> operator*(const Matrix<N>& rhs) const;
    Matrix<N> operator*(float k) const;
    Matrix<N> operator/(float k) const;
    bool operator==(const Matrix<N>& rhs) const;

    Matrix<N> transpose() const;
    // TODO: Mat4 determinant & inverse

   private:
    float _m[4][4];
};

template <size_t N>
Matrix<N>::Matrix() : _m() {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            _m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

template <size_t N>
Matrix<N> Matrix<N>::Identity() {
    Matrix<N> result;
    for (size_t i = 0; i < N; ++i) {
        result._m[i][i] = 1.0f;
    }
    return result;
}

template <size_t N>
float Matrix<N>::operator[](size_t n) const {
    if (n < 16) {
        return _m[n / N][n % N];
    } else {
        return _m[0][0];
    }
}

template <size_t N>
Matrix<N> Matrix<N>::operator+(const Matrix<N>& rhs) const {
    Matrix<N> result;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            result._m[i][j] = _m[i][j] + rhs._m[i][j];
        }
    }
    return result;
}

template <size_t N>
Matrix<N> Matrix<N>::operator-(const Matrix<N>& rhs) const {
    Matrix<N> result;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            result._m[i][j] = _m[i][j] - rhs._m[i][j];
        }
    }
    return result;
}

template <size_t N>
Matrix<N> Matrix<N>::operator*(const Matrix<N>& rhs) const {
    Matrix<N> result;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            result._m[i][j] = 0;
            for (size_t k = 0; k < N; k++) {
                result._m[i][j] += _m[i][k] * rhs._m[k][j];
            }
        }
    }
    return result;
}

template <size_t N>
Matrix<N> Matrix<N>::operator*(float k) const {
    Matrix<N> result;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            result._m[i][j] = _m[i][j] * k;
        }
    }
    return result;
}

template <size_t N>
Matrix<N> Matrix<N>::operator/(float k) const {
    Matrix<N> result;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            result._m[i][j] = _m[i][j] / k;
        }
    }
    return result;
}

template <size_t N>
bool Matrix<N>::operator==(const Matrix<N>& rhs) const {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (std::abs(_m[i][j] - rhs._m[i][j]) > 1e-6) {
                return false;
            }
        }
    }
    return true;
}

template <size_t N>
Matrix<N> Matrix<N>::transpose() const {
    Matrix<N> result;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result._m[i][j] = _m[j][i];
        }
    }
    return result;
}

using Matrix4 = Matrix<4>;
}  // namespace RenderBase