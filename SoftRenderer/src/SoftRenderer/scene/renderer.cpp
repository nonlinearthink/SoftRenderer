#include "SoftRenderer/scene/renderer.h"

#include <algorithm>
#include <cmath>

#include "SoftRenderer/math/color.h"
#include "SoftRenderer/math/vec.hpp"

using namespace SoftRenderer;

void Renderer::PrepareRender(uint32_t *frameBuffer) {
    frameBuffer_ = frameBuffer;
}

/**
 * @brief clear frameBuffer
 */
void Renderer::Clear() {
    auto color_data = static_cast<uint32_t>(background);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            frameBuffer_[j * width + i] = color_data;
        }
    }
}

/**
 * @brief put pixel color
 */
void Renderer::PutPixel(const Vector2i &p, const Color &color) {
    frameBuffer_[p.y * width + p.x] = static_cast<uint32_t>(color);
}

/**
 * @brief draw a line
 *
 * use digital differential analyzer
 */
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

/**
 * @brief draw a wireframe triangle
 */
void Renderer::DrawWireframeTriangle(const Vector2i &p0, const Vector2i &p1,
                                     const Vector2i &p2, const Color &color) {
    DrawLine(p0, p1, color);
    DrawLine(p1, p2, color);
    DrawLine(p2, p0, color);
}

/**
 * @brief draw a filled triangle
 *
 * use bounding rect and barycentric coordinate system
 */
void Renderer::DrawFilledTriangle(const Vector2i &p0, const Vector2i &p1,
                                  const Vector2i &p2, const Color &color) {
    // Bounding Rect
    Vector2i min(0, 0);
    Vector2i max(width - 1, height - 1);
    min.x = std::max(min.x, std::min(p0.x, std::min(p1.x, p2.x)));
    min.y = std::max(min.y, std::min(p0.y, std::min(p1.y, p2.y)));
    max.x = std::min(max.x, std::max(p0.x, std::max(p1.x, p2.x)));
    max.y = std::min(max.y, std::max(p0.y, std::max(p1.y, p2.y)));

    for (int y = min.y; y <= max.y; y++) {
        for (int x = min.x; x <= max.x; x++) {
            Vector3i vx(p1.x - p0.x, p2.x - p0.x, p0.x - x);
            Vector3i vy(p1.y - p0.y, p2.y - p0.y, p0.y - y);

            Vector3i u = vx.Cross(vy);

            if (std::abs(u.z) < 1) {
                continue;
            }

            Vector3f barycentric(1.f - (u.x + u.y) / (float)u.z,
                                 u.x / (float)u.z, u.y / (float)u.z);
            if (barycentric.x > 0 && barycentric.x < 1 && barycentric.y > 0 &&
                barycentric.y < 1 && barycentric.z > 0 && barycentric.z < 1) {
                PutPixel(Vector2i(x, y), color);
            }
        }
    }
}
