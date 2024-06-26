#include "SoftRenderer/renderer.h"

#include <iostream>

#include "SoftRenderer/shader_context.h"
#include "SoftRenderer/transform.h"

using namespace SoftRenderer;

void Renderer::Clear() {
    auto color_data = static_cast<u32>(background_);
    for (int i = 0; i < width_; i++) {
        for (int j = 0; j < height_; j++) {
            frame_buffer_[j * width_ + i] = color_data;
        }
    }
}

void Renderer::DrawPrimitive(Vertex v0, Vertex v1, Vertex v2) {
    auto context0 = ShaderContext();
    auto context1 = ShaderContext();
    auto context2 = ShaderContext();

    auto position0 = shader_program_->VertexShader(v0, context0);
    auto position1 = shader_program_->VertexShader(v1, context1);
    auto position2 = shader_program_->VertexShader(v2, context2);

    std::cout << position0 << position1 << position2 << std::endl;
}

void Renderer::Render() {
    if (!frame_buffer_) {
        return;
    }
    Clear();
    auto vertex_size = static_cast<int>(vertex_buffer_.size());
    auto index_size = static_cast<int>(index_buffer_.size());
    for (int i = 0; i <= index_size - 3; i++) {
        auto v0 = vertex_buffer_[index_buffer_[i] % vertex_size];
        auto v1 = vertex_buffer_[index_buffer_[i + 1] % vertex_size];
        auto v2 = vertex_buffer_[index_buffer_[i + 2] % vertex_size];
        DrawPrimitive(v0, v1, v2);
    }
}

void Renderer::PutPixel(const Vector2i &p, const Color &color) {
    frame_buffer_[p.y * width_ + p.x] = static_cast<u32>(color);
}

void Renderer::DrawLine2D(const Vector2i &p0, const Vector2i &p1,
                          const Color &color) {
    // Digital Differential Analyzer
    int dx = p1.x - p0.x;
    int dy = p1.y - p0.y;

    int steps = std::max(std::abs(dx), std::abs(dy));

    float x_increase = static_cast<float>(dx) / static_cast<float>(steps);
    float y_increase = static_cast<float>(dy) / static_cast<float>(steps);

    auto x_paint = static_cast<float>(p0.x);
    auto y_paint = static_cast<float>(p0.y);
    for (int i = 0; i <= steps; i++) {
        PutPixel(Vector2i(static_cast<int>(round(x_paint)),
                          static_cast<int>(round(y_paint))),
                 color);
        x_paint += x_increase;
        y_paint += y_increase;
    }
}

void Renderer::DrawWireframeTriangle2D(const Vector2i &p0, const Vector2i &p1,
                                       const Vector2i &p2, const Color &color) {
    DrawLine2D(p0, p1, color);
    DrawLine2D(p1, p2, color);
    DrawLine2D(p2, p0, color);
}

void Renderer::DrawTriangle2D(const Vector2i &p0, const Vector2i &p1,
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

            Vector3f barycentric(
                1.f - static_cast<float>(u.x + u.y) / static_cast<float>(u.z),
                static_cast<float>(u.x) / static_cast<float>(u.z),
                static_cast<float>(u.y) / static_cast<float>(u.z));
            if (barycentric.x > 0 && barycentric.x < 1 && barycentric.y > 0 &&
                barycentric.y < 1 && barycentric.z > 0 && barycentric.z < 1) {
                PutPixel(Vector2i(x, y), color);
            }
        }
    }
}
