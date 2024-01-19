#pragma once

#include <algorithm>
#include <cstdint>

#include "SoftRenderer/common.h"

namespace SoftRenderer {
// Color Class
class Color {
public:
    float r, g, b, a;

    Color(float r, float g, float b) : r{r}, g{g}, b{b}, a{1} {}
    Color(float r, float g, float b, float a) : r{r}, g{g}, b{b}, a{a} {}

    static inline Color White() { return {1, 1, 1}; };
    static inline Color Black() { return {0, 0, 0}; };
    static inline Color Red() { return {1, 0, 0}; };
    static inline Color Green() { return {0, 1, 0}; };
    static inline Color Blue() { return {0, 0, 1}; };

    inline Color operator+(const Color& rhs) const;
    inline Color operator-(const Color& rhs) const;
    inline Color operator*(float k) const;
    inline Color operator/(float k) const;
    explicit constexpr operator uint32_t() const;

    inline void CopyFrom(const Color& color);
};

inline Color Color::operator+(const Color& rhs) const {
    const auto min = 0.f;
    const auto max = 1.f;
    const float r = std::clamp(r + rhs.r, min, max);
    const float g = std::clamp(g + rhs.g, min, max);
    const float b = std::clamp(b + rhs.b, min, max);
    return {r, g, b};
}

inline Color Color::operator-(const Color& rhs) const {
    const auto min = 0.f;
    const auto max = 1.f;
    const float r = std::clamp(r - rhs.r, min, max);
    const float g = std::clamp(g - rhs.g, min, max);
    const float b = std::clamp(b - rhs.b, min, max);
    return {r, g, b};
}

inline Color Color::operator*(const float k) const {
    const auto min = 0.f;
    const auto max = 1.f;
    const float r = std::clamp(r * k, min, max);
    const float g = std::clamp(g * k, min, max);
    const float b = std::clamp(b * k, min, max);
    return {r, g, b};
}

inline Color Color::operator/(const float k) const {
    const auto min = 0.f;
    const auto max = 1.f;
    const float r = std::clamp(r / k, min, max);
    const float g = std::clamp(g / k, min, max);
    const float b = std::clamp(b / k, min, max);
    return {r, g, b};
}

constexpr Color::operator uint32_t() const {
    return (static_cast<uint32_t>(r * 255) << 24) |
           (static_cast<uint32_t>(g * 255) << 16) |
           (static_cast<uint32_t>(b * 255) << 8) | static_cast<uint32_t>(255);
}

inline void Color::CopyFrom(const Color& color) {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
}
}  // namespace SoftRenderer
