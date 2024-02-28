// Set SDL Main Entry Point
#define SDL_MAIN_HANDLED

#include "SDLApplication.h"
#include "SoftRenderer.h"

int main() {
    auto renderer = std::make_unique<SoftRenderer::Renderer>(800, 600);
    renderer->scene.LoadAssetsFromFile("assets/cube.obj");

    auto app = std::make_unique<SDLApplication>("OBJ Mesh", renderer);
    if (!app->Initialize()) {
        return 1;
    }
    app->MainLoop();
    app->Destroy();
    return 0;
}
