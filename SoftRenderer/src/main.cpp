#define SDL_MAIN_HANDLED

#include <algorithm>
#include <cmath>
#include <memory>

#include "SDL.h"

class SoftRenderer {
public:
    int width, height;

    SoftRenderer(int _width, int _height) : width(_width), height(_height) {}
    ~SoftRenderer() {}

    void prepareRender(Uint32* frameBuffer) { _frameBuffer = frameBuffer; }

    void putPixel(int x, int y, Uint32 color) {
        *(_frameBuffer + (y * width + x)) = color;
    }

    void drawLine(int x0, int y0, int x1, int y1) {
        // Digital Differential Analyzer
        int dx = x1 - x0;
        int dy = y1 - y0;

        int steps = std::max(std::abs(dx), std::abs(dy));

        float xInc = dx / (float)steps;
        float yInc = dy / (float)steps;

        float xUpdate = x0;
        float yUpdate = y0;
        for (int i = 0; i <= steps; i++) {
            putPixel(round(xUpdate), round(yUpdate), 0xFFFFFFFF);
            xUpdate += xInc;
            yUpdate += yInc;
        }
    }

private:
    Uint32* _frameBuffer;
};

class SoftRenderApplication {
public:
    int width, height;
    bool running;

    SoftRenderApplication(int _width, int _height)
        : width(_width), height(_height), running(true) {
        _softRenderer = std::make_unique<SoftRenderer>(width, height);
    }
    ~SoftRenderApplication() {
        SDL_DestroyTexture(_rtt);
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    static std::unique_ptr<SoftRenderApplication> createApplication(
        int width, int height) {
        auto app = std::make_unique<SoftRenderApplication>(width, height);

        if (SDL_Init(SDL_INIT_EVENTS) < 0) {
            SDL_Log("SDL init failed");
            return nullptr;
        }

        app->_window = SDL_CreateWindow(
            "SoftRenderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (!app->_window) {
            SDL_Log("create window failed.");
            SDL_Quit();
            return nullptr;
        }

        app->_renderer = SDL_CreateRenderer(app->_window, -1, 0);
        if (!app->_renderer) {
            SDL_Log("create renderer failed.");
            SDL_Quit();
            return nullptr;
        }

        app->_rtt = SDL_CreateTexture(app->_renderer, SDL_PIXELFORMAT_RGBA8888,
                                      0, width, height);
        if (!app->_rtt) {
            SDL_Log("create renderer target texture failed.");
            SDL_Quit();
            return nullptr;
        }

        app->_event = std::make_unique<SDL_Event>();

        return app;
    }

    void tick() {
        while (SDL_PollEvent(_event.get())) {
            if (_event->type == SDL_QUIT) {
                running = false;
                return;
            }
        }

        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);

        SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(
            0, width, height, 32, SDL_PIXELFORMAT_RGBA8888);
        _softRenderer->prepareRender((Uint32*)surface->pixels);

        render();

        SDL_UpdateTexture(_rtt, NULL, surface->pixels, surface->pitch);
        SDL_FreeSurface(surface);

        SDL_RenderCopy(_renderer, _rtt, NULL, NULL);

        SDL_RenderPresent(_renderer);
        SDL_Delay(1000 / 60);
    }

private:
    std::unique_ptr<SoftRenderer> _softRenderer;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    SDL_Texture* _rtt;
    std::unique_ptr<SDL_Event> _event;

    void render() { _softRenderer->drawLine(0, 0, width / 2, height / 2); }
};

int main(int argc, char* argv[]) {
    const int width = 640;
    const int height = 480;

    auto app = SoftRenderApplication::createApplication(width, height);
    if (app == nullptr) {
        return 1;
    }

    while (app->running) {
        app->tick();
    }

    return 0;
}
