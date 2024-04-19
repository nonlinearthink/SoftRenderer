#pragma once

#include <algorithm>

#include "SoftRenderer/common.h"

namespace SoftRenderer {
// Color Class
class Color {
public:
    float r, g, b, a;

    Color() : r{0}, g{0}, b{0}, a{1} {}
    Color(float r, float g, float b) : r{r}, g{g}, b{b}, a{1} {}
    Color(float r, float g, float b, float a) : r{r}, g{g}, b{b}, a{a} {}

    static inline Color White() { return {1, 1, 1}; };
    static inline Color Black() { return {0, 0, 0}; };
    static inline Color Red() { return {1, 0, 0}; };
    static inline Color Green() { return {0, 1, 0}; };
    static inline Color Blue() { return {0, 0, 1}; };

    inline Color operator+(const Color& rhs) const {
        return {std::clamp(r + rhs.r, MIN_COMPONENT, MAX_COMPONENT),
                std::clamp(g + rhs.g, MIN_COMPONENT, MAX_COMPONENT),
                std::clamp(b + rhs.b, MIN_COMPONENT, MAX_COMPONENT),
                std::clamp(a + rhs.a, MIN_COMPONENT, MAX_COMPONENT)};
    }
    inline Color operator-(const Color& rhs) const {
        return {std::clamp(r - rhs.r, MIN_COMPONENT, MAX_COMPONENT),
                std::clamp(g - rhs.g, MIN_COMPONENT, MAX_COMPONENT),
                std::clamp(b - rhs.b, MIN_COMPONENT, MAX_COMPONENT),
                std::clamp(a - rhs.a, MIN_COMPONENT, MAX_COMPONENT)};
    }
    inline Color operator*(float k) const {
        return {std::clamp(r * k, MIN_COMPONENT, MAX_COMPONENT),
                std::clamp(g * k, MIN_COMPONENT, MAX_COMPONENT),
                std::clamp(b * k, MIN_COMPONENT, MAX_COMPONENT),
                std::clamp(a * k, MIN_COMPONENT, MAX_COMPONENT)};
    }
    inline Color operator/(float k) const {
        return {std::clamp(r / k, MIN_COMPONENT, MAX_COMPONENT),
                std::clamp(g / k, MIN_COMPONENT, MAX_COMPONENT),
                std::clamp(b / k, MIN_COMPONENT, MAX_COMPONENT),
                std::clamp(a / k, MIN_COMPONENT, MAX_COMPONENT)};
    }
    inline bool operator==(const Color& rhs) const {
        using namespace MathUtils;
        return Equals(r, rhs.r) && Equals(g, rhs.g) && Equals(b, rhs.b) &&
               Equals(a, rhs.a);
    }
    inline bool operator!=(const Color& rhs) const {
        using namespace MathUtils;
        return !Equals(r, rhs.r) || !Equals(g, rhs.g) || !Equals(b, rhs.b) ||
               !Equals(a, rhs.a);
    }
    constexpr explicit operator u32() const {
        return (static_cast<u32>(r * 255) << 24) |
               (static_cast<u32>(g * 255) << 16) |
               (static_cast<u32>(b * 255) << 8) | static_cast<u32>(255);
    }

    inline void CopyFrom(const Color& color) noexcept {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
    }

private:
    static constexpr float MIN_COMPONENT = 0.f;
    static constexpr float MAX_COMPONENT = 1.f;
};
}  // namespace SoftRenderer
