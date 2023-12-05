#pragma once

#include <cmath>

namespace SoftRenderer {
class Quaternion {
public:
    float x, y, z, w;

    Quaternion(float x = 0.0, float y = 0.0, float z = 0.0, float w = 1.0)
        : x(x), y(y), z(z), w(w) {}

    Quaternion operator*(const Quaternion& q) const;

    Quaternion Conjugate() const;

    float Norm() const;

    Quaternion Normalize() const;
};
};  // namespace SoftRenderer
