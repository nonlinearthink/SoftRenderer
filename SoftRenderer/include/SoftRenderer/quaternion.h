#pragma once

#include <cmath>

namespace SoftRenderer {
class Quaternion {
public:
    float x, y, z, w;

    explicit Quaternion(float x = 0.0, float y = 0.0, float z = 0.0,
                        float w = 1.0)
        : x{x}, y{y}, z{z}, w{w} {}

    Quaternion operator*(const Quaternion& q) const;

    [[nodiscard]] Quaternion Conjugate() const;
    [[nodiscard]] float Norm() const;
    [[nodiscard]] Quaternion Normalize() const;
};
};  // namespace SoftRenderer
