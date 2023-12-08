#include "SoftRenderer/math/matrix.h"

#include <algorithm>
#include <limits>

#include "SoftRenderer/math/common.h"

using namespace SoftRenderer;

Matrix::Matrix(float _m[4][4]) { std::copy(&_m[0][0], &_m[3][3] + 1, m); }

Matrix Matrix::Identity() {
    Matrix result;
    for (int i = 0; i < 4; i++) {
        result.m[i][i] = 1.0f;
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& rhs) const {
    Matrix result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m[i][j] + rhs.m[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
    Matrix result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m[i][j] - rhs.m[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
    Matrix result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                result.m[i][j] += m[i][k] * rhs.m[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(float k) const {
    Matrix result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m[i][j] * k;
        }
    }
    return result;
}

Matrix Matrix::operator/(float k) const {
    Matrix result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m[i][j] / k;
        }
    }
    return result;
}

bool Matrix::operator==(const Matrix& rhs) const {
    float epsilon = std::numeric_limits<float>::epsilon();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (!Equals(m[i][j], rhs.m[i][j])) {
                return false;
            }
        }
    }
    return true;
}

Matrix Matrix::Transpose() const {
    Matrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m[j][i];
        }
    }
    return result;
}

Vector3f Matrix::MultiplyVector(const Vector3f& vec) const {
    float x = m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z;
    float y = m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z;
    float z = m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z;
    Vector3f result(x, y, z);
    return result;
}
