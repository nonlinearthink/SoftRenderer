#include "SoftRenderer/renderer.h"

#include <algorithm>
#include <cmath>

#include "SoftRenderer/color.h"
#include "SoftRenderer/vec.h"

using namespace SoftRenderer;

void Renderer::PrepareRender(uint32_t *frame_buffer) {
    frame_buffer_ = frame_buffer;
}

void Renderer::Clear() {
    auto color_data = static_cast<uint32_t>(background_);
    for (int i = 0; i < width_; i++) {
        for (int j = 0; j < height_; j++) {
            frame_buffer_[j * width_ + i] = color_data;
        }
    }
}

void Renderer::PutPixel(const Vector2i &p, const Color &color) {
    frame_buffer_[p.y * width_ + p.x] = static_cast<uint32_t>(color);
}

void Renderer::DrawLine(const Vector2i &p0, const Vector2i &p1,
                        const Color &color) {
    // Digital Differential Analyzer
    int dx = p1.x - p0.x;
    int dy = p1.y - p0.y;

    int steps = std::max(std::abs(dx), std::abs(dy));

    float x_increase = (float)dx / (float)steps;
    float y_increase = (float)dy / (float)steps;

    auto x_paint = (float)p0.x;
    auto y_paint = (float)p0.y;
    for (int i = 0; i <= steps; i++) {
        PutPixel(Vector2i((int)round(x_paint), (int)round(y_paint)), color);
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
    // Bounding Rect
    Vector2i min{std::max(0, std::min(p0.x, std::min(p1.x, p2.x))),
                 std::max(0, std::min(p0.y, std::min(p1.y, p2.y)))};
    Vector2i max(std::min(width_ - 1, std::max(p0.x, std::max(p1.x, p2.x))),
                 std::min(height_ - 1, std::max(p0.y, std::max(p1.y, p2.y))));

    // Barycentric Coordinate System
    for (int y = min.y; y <= max.y; y++) {
        for (int x = min.x; x <= max.x; x++) {
            Vector3i vx(p1.x - p0.x, p2.x - p0.x, p0.x - x);
            Vector3i vy(p1.y - p0.y, p2.y - p0.y, p0.y - y);

            Vector3i u = vx.Cross(vy);

            if (std::abs(u.z) < 1) {
                continue;
            }

            Vector3f barycentric(1.f - (float)(u.x + u.y) / (float)u.z,
                                 (float)u.x / (float)u.z,
                                 (float)u.y / (float)u.z);
            if (barycentric.x > 0 && barycentric.x < 1 && barycentric.y > 0 &&
                barycentric.y < 1 && barycentric.z > 0 && barycentric.z < 1) {
                PutPixel(Vector2i(x, y), color);
            }
        }
    }
}
