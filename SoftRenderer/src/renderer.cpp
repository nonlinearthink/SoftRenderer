#include "renderer.h"

SoftRenderer::SoftRenderer(int _width, int _height, HWND hWnd)
    : width(_width), height(_height) {
    // create a device context in memory temporarily
    HDC hDC = GetDC(hWnd);
    _swapDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);

    // get a bitmap
    BITMAPINFO bitmapInfo = {{sizeof(BITMAPINFOHEADER), _width, -_height, 1, 32,
                              BI_RGB, (DWORD)_width * _height * 4, 0, 0, 0, 0}};
    _curBitmap = CreateDIBSection(_swapDC, &bitmapInfo, DIB_RGB_COLORS,
                                  (void**)&_frameBuffer, 0, 0);
    _oldBitmap = (HBITMAP)SelectObject(_swapDC, _curBitmap);

    // allocate depthBuffer
    _depthBuffer.reset(new float[_width * _height]);

    // init frameBuffer & depthBuffer
    clearBuffer();
}

SoftRenderer::~SoftRenderer() {
    if (_swapDC) {
        if (_oldBitmap) {
            SelectObject(_swapDC, _oldBitmap);
            _oldBitmap = nullptr;
        }
        DeleteDC(_swapDC);
        _swapDC = nullptr;
    }
    if (_curBitmap) {
        DeleteObject(_curBitmap);
        _curBitmap = nullptr;
    }
    delete[] _frameBuffer;
    _frameBuffer = nullptr;
}

void SoftRenderer::clearBuffer() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = i * width + j;
            _frameBuffer[index] = _bgColor;
            _depthBuffer[index] = 1.0f;
        }
    }
}

void SoftRenderer::update(HWND hWnd) {
    clearBuffer();

    // update the real device context from our swap device context
    HDC hDC = GetDC(hWnd);
    BitBlt(hDC, 0, 0, width, height, _swapDC, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hDC);
}
