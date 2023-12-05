#include <memory>

#include "SDL.h"
#include "SoftRenderer.h"

class RenderApplication {
public:
    int width, height;
    bool running;

    RenderApplication(int _width, int _height)
        : width(_width), height(_height), running(true) {
        soft_renderer_ =
            std::make_unique<SoftRenderer::Renderer>(width, height);
    }
    ~RenderApplication() {
        SDL_DestroyTexture(render_target_texture_);
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    static std::unique_ptr<RenderApplication> CreateApplication(int width,
                                                                int height) {
        auto app = std::make_unique<RenderApplication>(width, height);

        if (SDL_Init(SDL_INIT_EVENTS) < 0) {
            SDL_Log("SDL init failed");
            return nullptr;
        }

        app->window_ = SDL_CreateWindow(
            "SoftRenderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (!app->window_) {
            SDL_Log("create window failed.");
            SDL_Quit();
            return nullptr;
        }

        app->renderer_ = SDL_CreateRenderer(app->window_, -1, 0);
        if (!app->renderer_) {
            SDL_Log("create renderer failed.");
            SDL_Quit();
            return nullptr;
        }

        app->render_target_texture_ = SDL_CreateTexture(
            app->renderer_, SDL_PIXELFORMAT_RGBA8888, 0, width, height);
        if (!app->render_target_texture_) {
            SDL_Log("create renderer target texture failed.");
            SDL_Quit();
            return nullptr;
        }

        app->event_ = std::make_unique<SDL_Event>();

        return app;
    }

    void Tick() {
        while (SDL_PollEvent(event_.get())) {
            if (event_->type == SDL_QUIT) {
                running = false;
                return;
            }
        }

        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
        SDL_RenderClear(renderer_);

        SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(
            0, width, height, 32, SDL_PIXELFORMAT_RGBA8888);
        soft_renderer_->PrepareRender((Uint32*)surface->pixels);

        render();

        SDL_UpdateTexture(render_target_texture_, NULL, surface->pixels,
                          surface->pitch);
        SDL_FreeSurface(surface);

        SDL_RenderCopy(renderer_, render_target_texture_, NULL, NULL);

        SDL_RenderPresent(renderer_);
        SDL_Delay(1000 / 60);
    }

    void render() { soft_renderer_->DrawLine(0, 0, width / 2, height / 2); }

private:
    std::unique_ptr<SoftRenderer::Renderer> soft_renderer_;
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_Texture* render_target_texture_;
    std::unique_ptr<SDL_Event> event_;
};
