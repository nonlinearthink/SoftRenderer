#include "SoftRenderer/math/color.h"

SoftRenderer::Color::Color(float _r, float _g, float _b)
    : r(_r), g(_g), b(_b), a(1) {}

SoftRenderer::Color::Color(float _r, float _g, float _b, float _a)
    : r(_r), g(_g), b(_b), a(_a) {}

SoftRenderer::Color SoftRenderer::Color::White() { return Color(1, 1, 1); }

SoftRenderer::Color SoftRenderer::Color::Black() { return Color(0, 0, 0); }

SoftRenderer::Color SoftRenderer::Color::Red() { return Color(1, 0, 0); }

SoftRenderer::Color SoftRenderer::Color::Green() { return Color(0, 1, 0); }

SoftRenderer::Color SoftRenderer::Color::Blue() { return Color(0, 0, 1); }
