#include "renderbase/math/color.h"

RenderBase::Color::Color(float _r, float _g, float _b)
    : r(_r), g(_g), b(_b), a(1) {}

RenderBase::Color::Color(float _r, float _g, float _b, float _a)
    : r(_r), g(_g), b(_b), a(_a) {}

RenderBase::Color RenderBase::Color::White() { return Color(1, 1, 1); }

RenderBase::Color RenderBase::Color::Black() { return Color(0, 0, 0); }

RenderBase::Color RenderBase::Color::Red() { return Color(1, 0, 0); }

RenderBase::Color RenderBase::Color::Green() { return Color(0, 1, 0); }

RenderBase::Color RenderBase::Color::Blue() { return Color(0, 0, 1); }
