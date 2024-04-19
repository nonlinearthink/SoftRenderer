// Set SDL Main Entry Point
#define SDL_MAIN_HANDLED

#include "SDL_application.h"
#include "SoftRenderer.h"

int main() {
    auto app{std::make_unique<SDLApplication>("OBJ Mesh", 800, 600)};
    app->set_initialize_callback([](SoftRenderer::Renderer &renderer) {
        renderer.scene.LoadAssetsFromFile("assets/cube.obj");
    });
    app->set_render_callback([](SoftRenderer::Renderer &renderer) {
        renderer.Render();
    });
    app->Run();

    return 0;
}
