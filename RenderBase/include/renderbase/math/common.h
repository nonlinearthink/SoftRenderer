#pragma once

#include <cmath>

#include "renderbase/math/quaternion.h"

namespace RenderBase {
const double PI = std::acos(-1);

inline double DegreeToRadian(double degree) {
    return degree * (RenderBase::PI / 180);
}

inline double RadianToDegree(double radian) {
    return radian * (180 / RenderBase::PI);
}

template <typename T>
T Lerp(const T& lhs, const T& rhs, float t) {
    return (lhs * (1 - t)) + (rhs * t);
}

// Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t) {
//     float cosTheta = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
//     if (cosTheta < 0.0f) {
//         q2.w = -q2.w;
//         q2.x = -q2.x;
//         q2.y = -q2.y;
//         q2.z = -q2.z;
//         cosTheta = -cosTheta;
//     }

//     float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta);
//     if (std::abs(sinTheta) < 1e-6f) {
//         return q1;
//     }

//     float scale0 = std::sin((1.0f - t) * (PI / 2.0f)) / sinTheta;
//     float scale1 = std::sin(t * (PI / 2.0f)) / sinTheta;

//     return Quaternion(
//         scale0 * q1.x + scale1 * q2.x, scale0 * q1.y + scale1 * q2.y,
//         scale0 * q1.z + scale1 * q2.z, scale0 * q1.w + scale1 * q2.w);
// }
}  // namespace RenderBase
