#pragma once

#include <cstdint>

#include "SoftRenderer/math/color.h"
#include "SoftRenderer/math/matrix.hpp"
#include "SoftRenderer/math/vec.hpp"

namespace SoftRenderer {
class Renderer {
public:
    Renderer(int width, int height)
        : width_(width), height_(height), background_(Color::Black()){};
    ~Renderer() {}

    void set_background(const Color &background);

    void PrepareRender(uint32_t *frame_buffer);
    /**
     * @brief clear frameBuffer
     */
    void Clear();
    /**
     * @brief put pixel color
     */
    void PutPixel(const Vector2i &p, const Color &color);
    /**
     * @brief draw a line
     *
     * use digital differential analyzer
     */
    void DrawLine(const Vector2i &p0, const Vector2i &p1, const Color &color);
    /**
     * @brief draw a wireframe triangle
     */
    void DrawWireframeTriangle(const Vector2i &p0, const Vector2i &p1,
                               const Vector2i &p2, const Color &color);
    /**
     * @brief draw a filled triangle
     */
    void DrawFilledTriangle(const Vector2i &p0, const Vector2i &p1,
                            const Vector2i &p2, const Color &color);
    /**
     * @brief draw a 3d triangle
     *
     * test model, view, projection matrix
     */
    void Draw3DTriangle(const Vector3f &p0, const Vector3f &p1,
                        const Vector3f &p2, const Matrix4 &mvp);

private:
    int width_, height_;
    Color background_;
    uint32_t *frame_buffer_;
};
};  // namespace SoftRenderer
