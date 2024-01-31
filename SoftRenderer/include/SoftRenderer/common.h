#pragma once

#include <cmath>
#include <cstdint>
#include <limits>
#include <string>

typedef int32_t i32;
typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;

namespace MathUtils {
static constexpr float C_PI() noexcept {
#ifdef M_PI
    return M_PI;
#else
    return 3.141592653589793;
#endif
}

constexpr float DegreeToRadian(float degree) { return degree * (C_PI() / 180); }

constexpr float RadianToDegree(float radian) { return radian * (180 / C_PI()); }

template <typename T>
inline bool Equals(T lhs, T rhs) {
    static_assert(std::is_floating_point<T>::value,
                  "T must be a floating point type");
    T epsilon = std::numeric_limits<T>::epsilon();
    return std::abs(lhs - rhs) <=
           epsilon *
               std::max({std::abs(lhs), std::abs(rhs), static_cast<T>(1.0)});
}

template <typename T>
inline T Lerp(const T& lhs, const T& rhs, float t) {
    return (lhs * (1 - t)) + (rhs * t);
}
}  // namespace MathUtils

namespace StringUtils {
// Used to implement the ends_with function of std::string in standards before
// CXX20
bool EndsWith(const std::string& full_str, const std::string& end_str);
}  // namespace StringUtils
