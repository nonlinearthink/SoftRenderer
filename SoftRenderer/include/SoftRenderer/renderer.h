#pragma once

#include <cstdint>

#include "SoftRenderer/color.h"
#include "SoftRenderer/matrix.h"
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

    void BindFrameBuffer(u32 *frame_buffer);
    // Clear frameBuffer.
    void Clear();
    // Put pixel color.
    void PutPixel(const Vector2i &p, const Color &color);
    // Draw a line(digital differential analyzer).
    void DrawLine(const Vector2i &p0, const Vector2i &p1, const Color &color);
    // Draw a wireframe triangle.
    void DrawWireframeTriangle(const Vector2i &p0, const Vector2i &p1,
                               const Vector2i &p2, const Color &color);
    // Draw a filled triangle.
    void DrawFilledTriangle(const Vector2i &p0, const Vector2i &p1,
                            const Vector2i &p2, const Color &color);
    // Draw a triangle primitive.
    void DrawTrianglePrimitive(const Vector3f &p0, const Vector3f &p1,
                               const Vector3f &p2, const Matrix4 &mvp);

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
