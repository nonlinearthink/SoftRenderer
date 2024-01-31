#include "application.h"

#include <cassert>
#include <string>

SoftRendererApplication::SoftRendererApplication(int width, int height)
    : width_{width}, height_{height}, renderer_{width, height} {}

#ifdef _DEBUG
SoftRendererApplication::~SoftRendererApplication() {
    assert(window_);
    assert(window_surface_);
}
#endif

bool SoftRendererApplication::Initialize() {
    if (SDL_Init(SDL_INIT_EVENTS) < 0) {
        HandleSDLCrash("SDL init failed");
        return false;
    }

    window_ = SDL_CreateWindow("SoftRenderer", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, width_, height_,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window_) {
        HandleSDLCrash("create window failed.");
        return false;
    }

    window_surface_ = SDL_GetWindowSurface(window_);

    event_ = std::make_unique<SDL_Event>();

    return true;
}

bool SoftRendererApplication::LoadAssets(const std::string& path) {
    return renderer_.scene.LoadAssetsFromFile(path);
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

        // Create a render surface to get a frame buffer
        SDL_Surface* render_surface{SDL_CreateRGBSurfaceWithFormat(
            0, width_, height_, 32, SDL_PIXELFORMAT_RGBA8888)};
        renderer_.BeginDraw((u32*)render_surface->pixels);
        renderer_.Clear();

        // Do render job
        Render();

        // Copy the render surface to window surface
        SDL_BlitSurface(render_surface, nullptr, window_surface_, nullptr);
        SDL_UpdateWindowSurface(window_);

        // Free the render surface
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

void SoftRendererApplication::HandleSDLCrash(const std::string& message) {
    SDL_Log(message.c_str());
    Release();
}
