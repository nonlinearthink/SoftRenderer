#include "core/Matrix.h"

template <size_t N>
Matrix<N>::Matrix(): _m() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j)
                _m[i][j] = 1;
            else
                _m[i][j] = 0;
        }
    }
}

template <size_t N>
Matrix<N>::~Matrix() = default;

template <size_t N>
Matrix<N> Matrix<N>::operator+(const Matrix<N>& rhs) const {
    Matrix<N> result;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result._m[i][j] = _m[i][j] + rhs._m[i][j];
        }
    }
    return result;
}

template <size_t N>
Matrix<N> Matrix<N>::operator-(const Matrix<N>& rhs) const {
    Matrix<N> result;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result._m[i][j] = _m[i][j] - rhs._m[i][j];
        }
    }
    return result;
}

template <size_t N>
Matrix<N> Matrix<N>::operator*(const Matrix<N>& rhs) const {
    Matrix<N> result;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result._m[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result._m[i][j] += _m[i][k] * rhs._m[k][j];
            }
        }
    }
    return result;
}

template <size_t N>
Matrix<N> Matrix<N>::operator*(float k) const {
    Matrix<N> result;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result._m[i][j] = _m[i][j] * k;
        }
    }
    return result;
}

template <size_t N>
Matrix<N> Matrix<N>::operator/(float k) const {
    Matrix<N> result;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result._m[i][j] = _m[i][j] / k;
        }
    }
    return result;
}

template <size_t N>
bool Matrix<N>::operator==(const Matrix<N>& rhs) const {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (_m[i][j] != rhs._m[i][j]) {
                return false;
            }
        }
    }
    return true;
}
