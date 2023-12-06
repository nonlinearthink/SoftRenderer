#include <memory>

#include "SDL.h"
#include "SoftRenderer.h"

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
 * @brief Deleter of SDL_Renderer to implement smart pointer
 */
struct SDL_Renderer_Deleter {
    void operator()(SDL_Renderer* renderer) const {
        SDL_DestroyRenderer(renderer);
    }
};
/**
 *@brief Smart Pointer Implementation of SDL_Renderer
 */
using Unique_SDL_Renderer_Ptr =
    std::unique_ptr<SDL_Renderer, SDL_Renderer_Deleter>;

/**
 * @brief Deleter of SDL_Texture to implement smart pointer
 */
struct SDL_Texture_Deleter {
    void operator()(SDL_Texture* texture) const { SDL_DestroyTexture(texture); }
};
/**
 *@brief Smart Pointer Implementation of SDL_Texture
 */
using Unique_SDL_Texture_Ptr =
    std::unique_ptr<SDL_Texture, SDL_Texture_Deleter>;

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
        soft_renderer_ =
            std::make_unique<SoftRenderer::Renderer>(width, height);
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

        renderer_ =
            Unique_SDL_Renderer_Ptr(SDL_CreateRenderer(window_.get(), -1, 0));
        if (!renderer_) {
            SDL_Log("create renderer failed.");
            SDL_Quit();
            return false;
        }

        render_target_texture_ = Unique_SDL_Texture_Ptr(SDL_CreateTexture(
            renderer_.get(), SDL_PIXELFORMAT_RGBA8888, 0, width, height));
        if (!render_target_texture_) {
            SDL_Log("create renderer target texture failed.");
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

        SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);
        SDL_RenderClear(renderer_.get());

        Unique_SDL_Surface_Ptr surface(SDL_CreateRGBSurfaceWithFormat(
            0, width, height, 32, SDL_PIXELFORMAT_RGBA8888));
        soft_renderer_->PrepareRender((Uint32*)surface->pixels);

        render();

        SDL_UpdateTexture(render_target_texture_.get(), NULL, surface->pixels,
                          surface->pitch);

        SDL_RenderCopy(renderer_.get(), render_target_texture_.get(), NULL,
                       NULL);

        SDL_RenderPresent(renderer_.get());
        SDL_Delay(1000 / 60);
    }

    virtual void render() {}

protected:
    std::unique_ptr<SoftRenderer::Renderer> soft_renderer_;
    Unique_SDL_Window_Ptr window_;
    Unique_SDL_Renderer_Ptr renderer_;
    Unique_SDL_Texture_Ptr render_target_texture_;
    std::unique_ptr<SDL_Event> event_;
};
