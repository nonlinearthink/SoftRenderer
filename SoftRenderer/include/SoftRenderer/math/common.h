#pragma once

#include <cmath>
#include <limits>

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

namespace SoftRenderer {
static constexpr float pi() noexcept { return M_PI; }

inline double DegreeToRadian(double degree) { return degree * (pi() / 180); }

inline double RadianToDegree(double radian) { return radian * (180 / pi()); }

inline bool Equals(float lhs, float rhs) {
    float epsilon = std::numeric_limits<float>::epsilon();
    return std::abs(lhs - rhs) <= epsilon;
}

template <typename T>
T Lerp(const T& lhs, const T& rhs, float t) {
    return (lhs * (1 - t)) + (rhs * t);
}
}  // namespace SoftRenderer
