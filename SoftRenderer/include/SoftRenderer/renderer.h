#pragma once

#include "SoftRenderer/color.h"
#include "SoftRenderer/scene.h"
#include "SoftRenderer/vec.h"

namespace SoftRenderer {
class Renderer {
public:
    Scene scene;

    Renderer(int width, int height)
        : width_(width), height_(height), background_(Color::Black()){};

    [[nodiscard]] inline Color background() const;
    inline void set_background(const Color &background);

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
    void BeginDraw(u32 *frame_buffer);

private:
    int width_, height_;
    Color background_;
    u32 *frame_buffer_{nullptr};
};

inline Color Renderer::background() const { return background_; }

inline void Renderer::set_background(const Color &background) {
    background_.CopyFrom(background);
};
};  // namespace SoftRenderer
