#include "framework.h"

RenderApplication::RenderApplication(int _width, int _height)
    : width(_width), height(_height) {
    _renderer = std::make_unique<SoftRenderer::Renderer>(width, height);
}

RenderApplication::~RenderApplication() {
    // actually don't need to release because SDL_Window will handle it.
    _window_surface = nullptr;
    SDL_Quit();
}

bool RenderApplication::Initialize() {
    if (SDL_Init(SDL_INIT_EVENTS) < 0) {
        SDL_Log("SDL init failed");
        return false;
    }

    _window = SDL_Window_Ptr(SDL_CreateWindow(
        "SoftRenderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
        height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE));
    if (!_window) {
        SDL_Log("create window failed.");
        SDL_Quit();
        return false;
    }

    _window_surface = SDL_Surface_Ptr(SDL_GetWindowSurface(_window.get()));

    _event = std::make_unique<SDL_Event>();

    return true;
}

void RenderApplication::Run() {
    bool running = true;
    while (running) {
        while (SDL_PollEvent(_event.get())) {
            if (_event->type == SDL_QUIT) {
                running = false;
                return;
            }
        }

        // prepare renderer
        SDL_Surface_Ptr render_surface(SDL_CreateRGBSurfaceWithFormat(
            0, width, height, 32, SDL_PIXELFORMAT_RGBA8888));
        _renderer->PrepareRender((Uint32*)render_surface->pixels);

        // Clear renderer
        _renderer->Clear();

        // Do a custom render job
        Render();

        // Update renderer's surface to window's surface
        SDL_BlitSurface(render_surface.get(), nullptr, _window_surface.get(),
                        nullptr);
        SDL_UpdateWindowSurface(_window.get());

        // Keep a fixed frame rate
        SDL_Delay(1000 / 60);
    }
}
