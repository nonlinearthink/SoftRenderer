#pragma once

#include <cmath>
#include <cstdint>
#include <limits>
#include <string>

typedef int32_t i32;
typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;

/// NOLINTBEGIN(bugprone-macro-parentheses)
// Disable the default copy functions for a class.
#ifndef DISABLE_COPY
#define DISABLE_COPY(class_name)                     \
    explicit class_name(const class_name&) = delete; \
    class_name& operator=(const class_name&) = delete;
#endif

// Disable the default move functions for a class.
#ifndef DISABLE_MOVE
#define DISABLE_MOVE(class_name)                \
    explicit class_name(class_name&&) = delete; \
    class_name& operator=(class_name&&) = delete;
#endif

// Disable the default copy and move functions for a class.
#ifndef DISABLE_COPY_AND_MOVE
#define DISABLE_COPY_AND_MOVE(class_name) \
    DISABLE_COPY(class_name) DISABLE_MOVE(class_name)
#endif
/// NOLINTEND(bugprone-macro-parentheses)

namespace MathUtils {
// Get the pi.
static constexpr float C_PI() noexcept {
#ifdef M_PI
    return M_PI;
#else
    return 3.141592653589793;
#endif
}

// Convert degree to radian.
constexpr float DegreeToRadian(float degree) { return degree * (C_PI() / 180); }

// Convert radian to degree.
constexpr float RadianToDegree(float radian) { return radian * (180 / C_PI()); }

// Compare equality of two floating point numbers.
template <typename T>
inline bool Equals(T lhs, T rhs) {
    static_assert(std::is_floating_point<T>::value,
                  "T must be a floating point type");
    T epsilon = std::numeric_limits<T>::epsilon();
    return std::abs(lhs - rhs) <=
           epsilon *
               std::max({std::abs(lhs), std::abs(rhs), static_cast<T>(1.0)});
}
}  // namespace MathUtils

namespace StringUtils {
// Simple implementation of ends_with function of std::string, the C++20
// standard library.
bool EndsWith(const std::string& full_str, const std::string& end_str);

// Simple implementation of std::format, the C++20 standard library.
std::string Format(const std::string& fmt_str,
                   const std::initializer_list<const char*>& args);
}  // namespace StringUtils
