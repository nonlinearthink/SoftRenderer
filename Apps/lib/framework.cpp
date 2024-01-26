#include "framework.h"

SoftRendererApplication::SoftRendererApplication(int width, int height)
    : width_{width}, height_{height}, renderer_{width, height} {}

SoftRendererApplication::~SoftRendererApplication() {
#ifdef _DEBUG
    assert(window_);
    assert(window_surface_);
#endif
}

bool SoftRendererApplication::Initialize() {
    if (SDL_Init(SDL_INIT_EVENTS) < 0) {
        SDL_Log("SDL init failed");
        SDL_Quit();
        return false;
    }

    window_ = SDL_CreateWindow("SoftRenderer", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, width_, height_,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window_) {
        SDL_Log("create window failed.");
        SDL_Quit();
        return false;
    }

    window_surface_ = SDL_GetWindowSurface(window_);

    event_ = std::make_unique<SDL_Event>();

    return true;
}

void SoftRendererApplication::Run() {
    bool running = true;
    while (running) {
        while (SDL_PollEvent(event_.get())) {
            if (event_->type == SDL_QUIT) {
                running = false;
                return;
            }
        }

        // prepare renderer
        SDL_Surface* render_surface{SDL_CreateRGBSurfaceWithFormat(
            0, width_, height_, 32, SDL_PIXELFORMAT_RGBA8888)};
        renderer_.PrepareRender((Uint32*)render_surface->pixels);

        // Clear renderer
        renderer_.Clear();

        // Do a custom render job
        Render();

        // Update renderer's surface to window's surface
        SDL_BlitSurface(render_surface, nullptr, window_surface_, nullptr);
        SDL_UpdateWindowSurface(window_);

        SDL_FreeSurface(render_surface);

        // Keep a fixed frame rate
        SDL_Delay(1000 / 60);
    }
}

void SoftRendererApplication::Release() {
    if (window_) {
        // This will not only destroy window_, but also free window_surface_
        SDL_DestroyWindow(window_);
    }
    SDL_Quit();
}
