#include "SoftRenderer/scene/renderer.h"

#include <algorithm>
#include <cmath>

using namespace SoftRenderer;

void Renderer::PrepareRender(uint32_t* frameBuffer) {
    frameBuffer_ = frameBuffer;
}

void Renderer::PutPixel(int x, int y, uint32_t color) {
    frameBuffer_[y * width + x] = color;
}

void Renderer::DrawLine(int x0, int y0, int x1, int y1) {
    // Digital Differential Analyzer
    int dx = x1 - x0;
    int dy = y1 - y0;

    int steps = std::max(std::abs(dx), std::abs(dy));

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float xPaint = x0;
    float yPaint = y0;
    for (int i = 0; i <= steps; i++) {
        PutPixel(round(xPaint), round(yPaint), 0xFFFFFFFF);
        xPaint += xInc;
        yPaint += yInc;
    }
}
