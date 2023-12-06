
#pragma once

#include <cstdint>

#include "SoftRenderer/math/color.h"
#include "SoftRenderer/math/vec.hpp"

namespace SoftRenderer {
class Renderer {
public:
    int width, height;
    Color background;

    Renderer(int _width, int _height, const Color &_color)
        : width(_width), height(_height), background(_color){};
    ~Renderer() {}

    void PrepareRender(uint32_t *frameBuffer);
    void Clear();
    void PutPixel(const Vector2i &p, const Color &color);
    void DrawLine(const Vector2i &p0, const Vector2i &p1, const Color &color);
    void DrawWireframeTriangle(const Vector2i &p0, const Vector2i &p1,
                               const Vector2i &p2, const Color &color);
    void DrawFilledTriangle(const Vector2i &p0, const Vector2i &p1,
                            const Vector2i &p2, const Color &color);

private:
    uint32_t *frameBuffer_;
};
};  // namespace SoftRenderer
