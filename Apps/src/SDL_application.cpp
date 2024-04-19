#include "SDL_application.h"

bool SDLApplication::Initialize() {
    // Initialize SDL.
    if (SDL_Init(SDL_INIT_EVENTS) < 0) {
        HandleSDLError("SDL init failed");
        return false;
    }

    // Initialize the window.
    window_ = SDL_CreateWindow(title_.c_str(), SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, width_, height_,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window_) {
        HandleSDLError("create window failed.");
        return false;
    }

    // Get the window surface.
    window_surface_ = SDL_GetWindowSurface(window_);

    // Create SDL event.
    event_ = std::make_unique<SDL_Event>();

    // Call the user-defined callback to initialize the renderer.
    if (initialize_callback_) {
        initialize_callback_(renderer_);
    }

    return true;
}

void SDLApplication::Run() {
    if (!Initialize()) {
        return;
    }

    bool running = true;
    while (running) {
        while (SDL_PollEvent(event_.get())) {
            if (event_->type == SDL_QUIT) {
                running = false;
                return;
            }
        }

        // Create a render surface to get a frame buffer.
        SDL_Surface* render_surface{SDL_CreateRGBSurfaceWithFormat(
            0, width_, height_, 32, SDL_PIXELFORMAT_RGBA8888)};

        // Call the user-defined callback to render this frame.
        if (render_callback_) {
            renderer_.set_frame_buffer(
                reinterpret_cast<u32*>(render_surface->pixels));
            render_callback_(renderer_);
            renderer_.set_frame_buffer(nullptr);
        }

        // Copy the render surface to window surface.
        SDL_BlitSurface(render_surface, nullptr, window_surface_, nullptr);
        SDL_UpdateWindowSurface(window_);

        // Free the render surface.
        SDL_FreeSurface(render_surface);

        // Keep a fixed frame rate.
        SDL_Delay(1000 / 60);
    }

    Release();
}

void SDLApplication::Release() {
    if (window_) {
        // This will not only destroy window_, but also free window_surface_.
        SDL_DestroyWindow(window_);
    }
    SDL_Quit();
}

void SDLApplication::HandleSDLError(const std::string& message) {
    SDL_Log(message.c_str());
    Release();
}
