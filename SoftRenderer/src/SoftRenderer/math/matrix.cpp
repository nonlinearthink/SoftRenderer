#include "SoftRenderer/math/matrix.h"

#include <limits>

using namespace SoftRenderer;

Matrix::Matrix() : m_() {}

Matrix Matrix::Identity() {
    Matrix result;
    for (int i = 0; i < 4; ++i) {
        result.m_[i * 4] = 1.0f;
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& rhs) const {
    Matrix result;
    for (int i = 0; i < 16; ++i) {
        result.m_[i] = m_[i] + rhs.m_[i];
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
    Matrix result;
    for (int i = 0; i < 16; ++i) {
        result.m_[i] = m_[i] - rhs.m_[i];
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
    Matrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result.m_[i * 4 + j] += m_[i * 4 + k] * rhs.m_[k * 4 + j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(float k) const {
    Matrix result;
    for (int i = 0; i < 16; ++i) {
        result.m_[i] = m_[i] * k;
    }
    return result;
}

Matrix Matrix::operator/(float k) const {
    Matrix result;
    for (int i = 0; i < 16; ++i) {
        result.m_[i] = m_[i] / k;
    }
    return result;
}

bool Matrix::operator==(const Matrix& rhs) const {
    float epsilon = std::numeric_limits<float>::epsilon();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (std::abs(m_[i] - rhs.m_[i]) > epsilon) {
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
            result.m_[i * 4 + j] = m_[j * 4 + i];
        }
    }
    return result;
}

Vector3f Matrix::MultiplyVector(const Vector3f& vec) const {
    float x = m_[0] * vec.x + m_[1] * vec.y + m_[2] * vec.z;
    float y = m_[4] * vec.x + m_[5] * vec.y + m_[6] * vec.z;
    float z = m_[8] * vec.x + m_[9] * vec.y + m_[10] * vec.z;
    Vector3f result(x, y, z);
    return result;
}
