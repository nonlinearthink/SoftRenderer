#pragma once

#include <windows.h>

#include <memory>

class SoftRenderer {
public:
    int width, height;

    SoftRenderer(int _width, int _height, HWND hWnd);
    ~SoftRenderer();

    void clearBuffer();
    void update(HWND hWnd);

private:
    HDC _swapDC;
    HBITMAP _curBitmap;
    HBITMAP _oldBitmap;
    unsigned int* _frameBuffer = nullptr;
    std::shared_ptr<float[]> _depthBuffer = nullptr;
    // Default Color
    unsigned int _bgColor = ((123 << 16) | (195 << 8) | 221);
};
