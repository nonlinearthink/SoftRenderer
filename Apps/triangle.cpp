// Enable Visual Studio Memory Leak Test
#define _CRTDEG_MAP_ALLOC
#ifdef _DEBUG
#ifdef DBG_NEW
#define DEG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif
#endif
// Set SDL Main Entry Point
#define SDL_MAIN_HANDLED

#include "lib/framework.h"

class DrawTriangle : public SoftRendererApplication {
public:
    DrawTriangle(int width, int height) : SoftRendererApplication(width, height) {}

    void Render() override {
        renderer_.DrawFilledTriangle(
            SoftRenderer::Vector2i(width_ / 2, static_cast<int>(0.1 * height_)),
            SoftRenderer::Vector2i(static_cast<int>(0.1 * width_),
                                   static_cast<int>(0.9 * height_)),
            SoftRenderer::Vector2i(static_cast<int>(0.9 * width_),
                                   static_cast<int>(0.9 * height_)),
            SoftRenderer::Color::Green());
    }
};

int main(int argc, char* argv[]) {
    // Enable Visual Studio Memory Leak Test
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    const int width = 640;
    const int height = 480;

    auto app = std::make_unique<DrawTriangle>(width, height);
    if (!app->Initialize()) {
        return 1;
    }

    app->Run();

    app->Release();

    return 0;
}
