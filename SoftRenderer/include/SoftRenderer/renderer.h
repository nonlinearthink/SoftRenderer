#pragma once

#include <memory>
#include <vector>

#include "SoftRenderer/color.h"
#include "SoftRenderer/scene.h"
#include "SoftRenderer/shader_program.h"
#include "SoftRenderer/vec.h"
#include "SoftRenderer/vertex.h"

namespace SoftRenderer {
enum class RenderMode { WIREFRAME, SOLID, SHADED };

struct RenderState {
    Color background;
    RenderMode render_mode;

    RenderState()
        : background(Color::Black()), render_mode(RenderMode::SHADED) {}
};

class Renderer {
public:
    Scene scene;

    Renderer(int width, int height) : width_(width), height_(height){};
    Renderer(int width, int height, RenderState render_state)
        : width_(width), height_(height), render_state_(render_state) {}

    [[nodiscard]] inline int get_width() const { return width_; };
    [[nodiscard]] inline int get_height() const { return height_; };
    inline void set_frame_buffer(u32 *frame_buffer) {
        frame_buffer_ = frame_buffer;
    }
    inline void set_vertex_buffer(std::vector<Vertex> vertex_buffer) {
        vertex_buffer_ = std::move(vertex_buffer);
    }
    inline void set_shader_program(
        std::unique_ptr<IShaderProgram> shader_program) {
        shader_program_ = std::move(shader_program);
    }

    virtual void Render();

private:
    int width_, height_;
    RenderState render_state_;
    u32 *frame_buffer_{nullptr};
    std::vector<Vertex> vertex_buffer_;
    std::unique_ptr<IShaderProgram> shader_program_{nullptr};

    // Clear frameBuffer.
    void Clear();
    // Put pixel color.
    void PutPixel(const Vector2i &p, const Color &color);
    // Draw a line.
    void DrawLine2D(const Vector2i &p0, const Vector2i &p1, const Color &color);
    // Draw a wireframe triangle in screen space.
    void DrawWireframeTriangle2D(const Vector2i &p0, const Vector2i &p1,
                                 const Vector2i &p2, const Color &color);
    // Draw a filled triangle in screen space.
    void DrawTriangle2D(const Vector2i &p0, const Vector2i &p1,
                        const Vector2i &p2, const Color &color);
    // Draw a wireframe triangle in world space.
    void DrawWireframeTriangle(const Vector3f &p0, const Vector3f &p1,
                               const Vector3f &p2, const Matrix4 &matrix,
                               const Color &color);
    // Draw a filled triangle in world space.
    void DrawTriangle(const Vector3f &p0, const Vector3f &p1,
                      const Vector3f &p2, const Matrix4 &matrix,
                      const Color &color);
    // Draw a primitive
    void DrawPrimitive();
};
};  // namespace SoftRenderer
