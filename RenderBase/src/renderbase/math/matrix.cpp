#include "renderbase/math/matrix.h"

#include <limits>

RenderBase::Matrix::Matrix() : _m() {}

RenderBase::Matrix RenderBase::Matrix::Identity() {
    RenderBase::Matrix result;
    for (int i = 0; i < 4; ++i) {
        result._m[i * 4] = 1.0f;
    }
    return result;
}

RenderBase::Matrix RenderBase::Matrix::operator+(
    const RenderBase::Matrix& rhs) const {
    RenderBase::Matrix result;
    for (int i = 0; i < 16; ++i) {
        result._m[i] = _m[i] + rhs._m[i];
    }
    return result;
}

RenderBase::Matrix RenderBase::Matrix::operator-(
    const RenderBase::Matrix& rhs) const {
    RenderBase::Matrix result;
    for (int i = 0; i < 16; ++i) {
        result._m[i] = _m[i] - rhs._m[i];
    }
    return result;
}

RenderBase::Matrix RenderBase::Matrix::operator*(
    const RenderBase::Matrix& rhs) const {
    RenderBase::Matrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result._m[i * 4 + j] += _m[i * 4 + k] * rhs._m[k * 4 + j];
            }
        }
    }
    return result;
}

RenderBase::Matrix RenderBase::Matrix::operator*(float k) const {
    RenderBase::Matrix result;
    for (int i = 0; i < 16; ++i) {
        result._m[i] = _m[i] * k;
    }
    return result;
}

RenderBase::Matrix RenderBase::Matrix::operator/(float k) const {
    RenderBase::Matrix result;
    for (int i = 0; i < 16; ++i) {
        result._m[i] = _m[i] / k;
    }
    return result;
}

bool RenderBase::Matrix::operator==(const RenderBase::Matrix& rhs) const {
    float epsilon = std::numeric_limits<float>::epsilon();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (std::abs(_m[i] - rhs._m[i]) > epsilon) {
                return false;
            }
        }
    }
    return true;
}

RenderBase::Matrix RenderBase::Matrix::transpose() const {
    RenderBase::Matrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result._m[i * 4 + j] = _m[j * 4 + i];
        }
    }
    return result;
}

RenderBase::Vector3f RenderBase::Matrix::multiplyVector(
    const RenderBase::Vector3f& vec) const {
    float x = _m[0] * vec.x + _m[1] * vec.y + _m[2] * vec.z;
    float y = _m[4] * vec.x + _m[5] * vec.y + _m[6] * vec.z;
    float z = _m[8] * vec.x + _m[9] * vec.y + _m[10] * vec.z;
    RenderBase::Vector3f result(x, y, z);
    return result;
}
