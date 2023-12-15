#include <memory>

#include "SDL.h"
#include "SoftRenderer.h"

struct SDL_Window_Deleter {
    void operator()(SDL_Window* window) const { SDL_DestroyWindow(window); }
};
using Unique_SDL_Window_Ptr = std::unique_ptr<SDL_Window, SDL_Window_Deleter>;

struct SDL_Surface_Deleter {
    void operator()(SDL_Surface* surface) const { SDL_FreeSurface(surface); }
};
using Unique_SDL_Surface_Ptr =
    std::unique_ptr<SDL_Surface, SDL_Surface_Deleter>;

/**
 *@brief Base Class for All Application
 *
 * The main purpose is to wrap the interface of the SDL library
 */
class RenderApplication {
public:
    int width, height;
    bool running;

    RenderApplication(int _width, int _height)
        : width(_width), height(_height), running(true) {
        renderer_ = std::make_unique<SoftRenderer::Renderer>(width, height);
    }
    ~RenderApplication() {
        // don't need to release because window will handle it.
        window_surface_ = nullptr;
        SDL_Quit();
    }

    bool InitApplication() {
        if (SDL_Init(SDL_INIT_EVENTS) < 0) {
            SDL_Log("SDL init failed");
            return false;
        }

        window_ = Unique_SDL_Window_Ptr(SDL_CreateWindow(
            "SoftRenderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE));
        if (!window_) {
            SDL_Log("create window failed.");
            SDL_Quit();
            return false;
        }

        window_surface_ = SDL_GetWindowSurface(window_.get());

        event_ = std::make_unique<SDL_Event>();

        return true;
    }

    void Tick() {
        while (SDL_PollEvent(event_.get())) {
            if (event_->type == SDL_QUIT) {
                running = false;
                return;
            }
        }

        // prepare renderer
        Unique_SDL_Surface_Ptr render_surface(SDL_CreateRGBSurfaceWithFormat(
            0, width, height, 32, SDL_PIXELFORMAT_RGBA8888));
        renderer_->PrepareRender((Uint32*)render_surface->pixels);

        // Clear renderer
        renderer_->Clear();

        // Do a custom render job
        render();

        // Update renderer's surface to window's surface
        SDL_BlitSurface(render_surface.get(), NULL, window_surface_, NULL);
        // Update window's surface to screen
        SDL_UpdateWindowSurface(window_.get());

        // Keep a fixed frame rate
        SDL_Delay(1000 / 60);
    }

    virtual void render() {}

protected:
    std::unique_ptr<SoftRenderer::Renderer> renderer_;
    Unique_SDL_Window_Ptr window_;
    SDL_Surface* window_surface_;
    std::unique_ptr<SDL_Event> event_;
};
