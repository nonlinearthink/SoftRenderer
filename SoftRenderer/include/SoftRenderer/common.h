#pragma once

#include <cmath>
#include <cstdint>
#include <limits>

typedef int32_t i32;
typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;

static constexpr float C_PI() noexcept {
#ifdef M_PI
    return M_PI;
#else
    return 3.141592653589793;
#endif
}

constexpr double DegreeToRadian(double degree) {
    return degree * (C_PI() / 180);
}

constexpr double RadianToDegree(double radian) {
    return radian * (180 / C_PI());
}

inline bool Equals(float lhs, float rhs) {
    float epsilon = std::numeric_limits<float>::epsilon();
    return std::abs(lhs - rhs) <= epsilon;
}

template <typename T>
inline T Lerp(const T& lhs, const T& rhs, float t) {
    return (lhs * (1 - t)) + (rhs * t);
}
