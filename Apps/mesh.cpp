// Set SDL Main Entry Point
#define SDL_MAIN_HANDLED

#include "lib/application.h"

class MeshDemo : public SoftRendererApplication {
public:
    MeshDemo(int width, int height) : SoftRendererApplication(width, height) {}

    void Render() override {
        renderer_.DrawTriangle2D(
            SoftRenderer::Vector2i(width_ / 2, static_cast<int>(0.1 * height_)),
            SoftRenderer::Vector2i(static_cast<int>(0.1 * width_),
                                   static_cast<int>(0.9 * height_)),
            SoftRenderer::Vector2i(static_cast<int>(0.9 * width_),
                                   static_cast<int>(0.9 * height_)),
            SoftRenderer::Color::Green());
    }
};

int main() {
    const int width = 640;
    const int height = 480;

    auto app = std::make_unique<MeshDemo>(width, height);
    if (!app->Initialize()) {
        return 1;
    }
    if (!app->LoadAssets("assets/cube.obj")) {
        return 1;
    }

    app->Run();

    app->Release();
    return 0;
}
