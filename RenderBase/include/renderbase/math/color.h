#pragma once

namespace RenderBase {
class Color {
public:
    float r, g, b, a;

    Color(){};
    Color(float _r, float _g, float _b);
    Color(float _r, float _g, float _b, float _a);
    ~Color(){};

    static Color White();
    static Color Black();
    static Color Red();
    static Color Green();
    static Color Blue();

    inline Color operator+(const Color& rhs) const;
    inline Color operator-(const Color& rhs) const;
    inline Color operator*(const float k) const;
    inline Color operator/(const float k) const;
};

inline Color Color::operator+(const Color& rhs) const {
    return Color(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a);
}

inline Color Color::operator-(const Color& rhs) const {
    return Color(r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a);
}

inline Color Color::operator*(const float k) const {
    return Color(r * k, g * k, b * k, a * k);
}

inline Color Color::operator/(const float k) const {
    return Color(r / k, g / k, b / k, a / k);
}
}  // namespace RenderBase
