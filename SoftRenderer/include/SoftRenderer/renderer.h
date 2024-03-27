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

class Renderer {
public:
    Scene scene;

    Renderer(int width, int height)
        : width_{width}, height_{height}, background_{Color::Black()} {};

    // Get the width of the render image.
    [[nodiscard]] inline int get_width() const { return width_; };
    // Get the height of the render image.
    [[nodiscard]] inline int get_height() const { return height_; };
    // Set the background that is filled into the whole render image by default.
    inline void set_background(const Color& background) {
        background_ = background;
    }
    // Set the frame buffer of the render image.
    inline void set_frame_buffer(u32 *frame_buffer) {
        frame_buffer_ = frame_buffer;
    }
    // Set the vertex buffer, note the copy semantics here.
    void set_vertex_buffer(std::vector<Vertex> vertex_buffer) {
        vertex_buffer_ = std::move(vertex_buffer);
    }
    // Set the shader porgram, accepts a raw pointer.
    inline void set_shader_program(IShaderProgram *shader_program) {
        shader_program_ = std::shared_ptr<IShaderProgram>(shader_program);
    }
    // Set the shader porgram, accepts a shared_ptr.
    inline void set_shader_program(
        const std::shared_ptr<IShaderProgram> &shader_program) {
        shader_program_ = shader_program;
    }
    // Clear frame buffer with the background color.
    void Clear();
    // Draw a primitive.
    void DrawPrimitive();

private:
    int width_, height_;
    Color background_;
    u32 *frame_buffer_{nullptr};
    std::vector<Vertex> vertex_buffer_;
    std::shared_ptr<IShaderProgram> shader_program_{nullptr};

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
};
};  // namespace SoftRenderer
