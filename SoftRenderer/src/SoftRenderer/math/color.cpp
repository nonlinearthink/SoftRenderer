#include "SoftRenderer/math/color.h"

using namespace SoftRenderer;

Color::Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b), a(1) {}

Color::Color(float _r, float _g, float _b, float _a)
    : r(_r), g(_g), b(_b), a(_a) {}

Color Color::White() { return Color(1, 1, 1); }

Color Color::Black() { return Color(0, 0, 0); }

Color Color::Red() { return Color(1, 0, 0); }

Color Color::Green() { return Color(0, 1, 0); }

Color Color::Blue() { return Color(0, 0, 1); }

Color::operator uint32_t() const {
    return (static_cast<uint32_t>(r * 255) << 24) |
           (static_cast<uint32_t>(g * 255) << 16) |
           (static_cast<uint32_t>(b * 255) << 8) | static_cast<uint32_t>(255);
}
