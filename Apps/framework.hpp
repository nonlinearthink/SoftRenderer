#include <memory>

#include "SDL.h"
#include "SoftRenderer.h"
#include "SoftRenderer/math/color.h"

/**
 * @brief Deleter of SDL_Window to implement smart pointer
 */
struct SDL_Window_Deleter {
    void operator()(SDL_Window* window) const { SDL_DestroyWindow(window); }
};
/**
 *@brief Smart Pointer Implementation of SDL_Window
 */
using Unique_SDL_Window_Ptr = std::unique_ptr<SDL_Window, SDL_Window_Deleter>;

/**
 * @brief Deleter of SDL_Surface to implement smart pointer
 */
struct SDL_Surface_Deleter {
    void operator()(SDL_Surface* surface) const { SDL_FreeSurface(surface); }
};
/**
 *@brief Smart Pointer Implementation of SDL_Surface
 */
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
        renderer_ = std::make_unique<SoftRenderer::Renderer>(
            width, height, SoftRenderer::Color::Black());
    }
    ~RenderApplication() { SDL_Quit(); }

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

        surface_ = Unique_SDL_Surface_Ptr(SDL_GetWindowSurface(window_.get()));
        renderer_->PrepareRender((Uint32*)surface_->pixels);
        renderer_->Clear();

        render();

        SDL_UpdateWindowSurface(window_.get());
        SDL_Delay(1000 / 60);
    }

    virtual void render() {}

protected:
    std::unique_ptr<SoftRenderer::Renderer> renderer_;
    Unique_SDL_Window_Ptr window_;
    Unique_SDL_Surface_Ptr surface_;
    std::unique_ptr<SDL_Event> event_;
};
