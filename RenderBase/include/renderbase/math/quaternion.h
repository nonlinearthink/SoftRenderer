#pragma once

#include <cmath>

namespace RenderBase {
class Quaternion {
public:
    float x, y, z, w;

    Quaternion(float x = 0.0, float y = 0.0, float z = 0.0, float w = 1.0)
        : x(x), y(y), z(z), w(w) {}

    Quaternion operator*(const Quaternion& q) const;

    Quaternion conjugate() const;

    float norm() const;

    Quaternion normalize() const;
};
};  // namespace RenderBase
