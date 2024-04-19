#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <string>

#include "SDL.h"
#include "SoftRenderer.h"

class SDLApplication {
public:
    using InitializeCallback = std::function<void(SoftRenderer::Renderer&)>;
    using RenderCallback = InitializeCallback;

    SDLApplication(std::string title, int width, int height)
        : title_{std::move(title)},
          width_{width},
          height_{height},
          renderer_{width, height} {};
#ifdef _DEBUG
    ~SDLApplication() {
        assert(window_);
        assert(window_surface_);
    };
#endif

    // Set the user-defined initialize callback.
    inline void set_initialize_callback(InitializeCallback callback) {
        initialize_callback_ = std::move(callback);
    }
    // Set the user-defined render callback.
    inline void set_render_callback(RenderCallback callback) {
        render_callback_ = std::move(callback);
    }

    // Run the application, which will do the initialization, the application
    // main loop, and release the resources after the application exits in
    // sequence.
    void Run();

protected:
    std::string title_;
    int width_, height_;
    SDL_Window* window_{nullptr};
    SDL_Surface* window_surface_{nullptr};
    std::unique_ptr<SDL_Event> event_{nullptr};
    SoftRenderer::Renderer renderer_;
    InitializeCallback initialize_callback_{nullptr};
    RenderCallback render_callback_{nullptr};

    // Initialize the application, including the SDL framework, the window, the
    // renderer.
    bool Initialize();
    // Release the application resources.
    void Release();
    // Handle the error caused by SDL, and exit the application.
    void HandleSDLError(const std::string& message);
};
