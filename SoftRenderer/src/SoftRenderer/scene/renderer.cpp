#include "SoftRenderer/scene/renderer.h"

#include <algorithm>
#include <cmath>

#include "SoftRenderer/math/color.h"
#include "SoftRenderer/math/vec.hpp"

using namespace SoftRenderer;

void Renderer::PrepareRender(uint32_t *frameBuffer) {
    frameBuffer_ = frameBuffer;
}

void Renderer::Clear() {
    auto color_data = static_cast<uint32_t>(background);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            frameBuffer_[j * width + i] = color_data;
        }
    }
}

void Renderer::PutPixel(const Vector2i &p, const Color &color) {
    frameBuffer_[p.y * width + p.x] = static_cast<uint32_t>(color);
}

void Renderer::DrawLine(const Vector2i &p0, const Vector2i &p1,
                        const Color &color) {
    // Digital Differential Analyzer
    int dx = p1.x - p0.x;
    int dy = p1.y - p0.y;

    int steps = std::max(std::abs(dx), std::abs(dy));

    float x_increase = dx / (float)steps;
    float y_increase = dy / (float)steps;

    float x_paint = p0.x;
    float y_paint = p0.y;
    for (int i = 0; i <= steps; i++) {
        PutPixel(Vector2i(round(x_paint), round(y_paint)), color);
        x_paint += x_increase;
        y_paint += y_increase;
    }
}

void Renderer::DrawWireframeTriangle(const Vector2i &p0, const Vector2i &p1,
                                     const Vector2i &p2, const Color &color) {
    DrawLine(p0, p1, color);
    DrawLine(p1, p2, color);
    DrawLine(p2, p0, color);
}

void Renderer::DrawFilledTriangle(const Vector2i &p0, const Vector2i &p1,
                                  const Vector2i &p2, const Color &color) {
    // TODO: Draw Filled Triangle
}
