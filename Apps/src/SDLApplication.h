#pragma once

#include <SDL.h>

#include <cassert>
#include <memory>
#include <string>

#include "SoftRenderer.h"

class SDLApplication {
public:
    SDLApplication(std::string title,
                   std::unique_ptr<SoftRenderer::Renderer>& renderer)
        : title_{std::move(title)},
          width_{renderer->get_width()},
          height_{renderer->get_height()},
          renderer_{std::move(renderer)} {};
#ifdef _DEBUG
    ~SDLApplication() {
        assert(window_);
        assert(window_surface_);
    };
#endif

    bool Initialize();
    void MainLoop();
    void Destroy();

private:
    std::string title_;
    int width_, height_;
    SDL_Window* window_{nullptr};
    SDL_Surface* window_surface_{nullptr};
    std::unique_ptr<SDL_Event> event_{nullptr};
    std::unique_ptr<SoftRenderer::Renderer> renderer_;

    void HandleSDLError(const std::string& message);
};
