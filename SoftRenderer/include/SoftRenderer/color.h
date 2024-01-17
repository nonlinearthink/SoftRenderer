#pragma once

#include <algorithm>
#include <cstdint>

#include "SoftRenderer/common.h"

namespace SoftRenderer {
// Color Class
class Color {
public:
    Color(float r, float g, float b) : r_{r}, g_{g}, b_{b}, a_{1} {}
    Color(float r, float g, float b, float a) : r_{r}, g_{g}, b_{b}, a_{a} {}
    Color(const Color& color) {
        r_ = color.r_;
        g_ = color.g_;
        b_ = color.b_;
        a_ = color.a_;
    }

    inline static Color White() { return {1, 1, 1}; }
    inline static Color Black() { return {0, 0, 0}; }
    inline static Color Red() { return {1, 0, 0}; }
    inline static Color Green() { return {0, 1, 0}; }
    inline static Color Blue() { return {0, 0, 1}; }

    [[nodiscard]] constexpr float r() const { return r_; }
    [[nodiscard]] constexpr float g() const { return g_; }
    [[nodiscard]] constexpr float b() const { return b_; }
    [[nodiscard]] constexpr float a() const { return a_; }

    inline Color operator+(const Color& rhs) const;
    inline Color operator-(const Color& rhs) const;
    inline Color operator*(float k) const;
    inline Color operator/(float k) const;
    explicit constexpr operator uint32_t() const;

    inline void CopyFrom(const Color& color);

private:
    float r_, g_, b_, a_;
};

inline Color Color::operator+(const Color& rhs) const {
    const auto min = (float)0;
    const auto max = (float)1;
    const float r = std::clamp(r_ + rhs.r_, min, max);
    const float g = std::clamp(g_ + rhs.g_, min, max);
    const float b = std::clamp(b_ + rhs.b_, min, max);
    return {r, g, b};
}

inline Color Color::operator-(const Color& rhs) const {
    const auto min = (float)0;
    const auto max = (float)1;
    const float r = std::clamp(r_ - rhs.r_, min, max);
    const float g = std::clamp(g_ - rhs.g_, min, max);
    const float b = std::clamp(b_ - rhs.b_, min, max);
    return {r, g, b};
}

inline Color Color::operator*(const float k) const {
    const auto min = (float)0;
    const auto max = (float)1;
    const float r = std::clamp(r_ * k, min, max);
    const float g = std::clamp(g_ * k, min, max);
    const float b = std::clamp(b_ * k, min, max);
    return {r, g, b};
}

inline Color Color::operator/(const float k) const {
    const auto min = (float)0;
    const auto max = (float)1;
    const float r = std::clamp(r_ / k, min, max);
    const float g = std::clamp(g_ / k, min, max);
    const float b = std::clamp(b_ / k, min, max);
    return {r, g, b};
}

constexpr Color::operator uint32_t() const {
    return (static_cast<uint32_t>(r_ * 255) << 24) |
           (static_cast<uint32_t>(g_ * 255) << 16) |
           (static_cast<uint32_t>(b_ * 255) << 8) | static_cast<uint32_t>(255);
}

inline void Color::CopyFrom(const Color& color) {
    r_ = color.r_;
    g_ = color.g_;
    b_ = color.b_;
    a_ = color.a_;
}
}  // namespace SoftRenderer
