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

#include "framework.hpp"

class DrawTriangle : public RenderApplication {
public:
    DrawTriangle(int width, int height) : RenderApplication(width, height) {}

    void render() override {
        renderer_->DrawWireframeTriangle(
            SoftRenderer::Vector2i(width / 2, 0.1 * height),
            SoftRenderer::Vector2i(0.1 * width, 0.9 * height),
            SoftRenderer::Vector2i(0.9 * width, 0.9 * height),
            SoftRenderer::Color::White());
    }
};

int main(int argc, char* argv[]) {
    // Enable Visual Studio Memory Leak Test
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    const int width = 640;
    const int height = 480;

    auto app = std::make_unique<DrawTriangle>(width, height);
    if (!app->InitApplication()) {
        return 1;
    }

    while (app->running) {
        app->Tick();
    }

    return 0;
}
