
#pragma once

#include <cstdint>

namespace SoftRenderer {
class Renderer {
public:
    int width, height;

    Renderer(int _width, int _height) : width(_width), height(_height){};
    ~Renderer() {}

    void PrepareRender(uint32_t* frameBuffer);
    void PutPixel(int x, int y, uint32_t color);
    void DrawLine(int x0, int y0, int x1, int y1);

private:
    uint32_t* frameBuffer_;
};
};  // namespace SoftRenderer
