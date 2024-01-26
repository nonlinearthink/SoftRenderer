#include <cassert>
#include <memory>

#include "SDL.h"
#include "SoftRenderer.h"

/**
 * @brief Base Class for All Application
 *
 * Used to wrap the interface of the SDL library
 */
class SoftRendererApplication {
public:
    SoftRendererApplication(int _width, int _height);
    ~SoftRendererApplication();

    bool Initialize();
    void Run();
    void Release();

    virtual void Render(){};

protected:
    int width_, height_;
    SoftRenderer::Renderer renderer_;

private:
    SDL_Window* window_{nullptr};
    SDL_Surface* window_surface_{nullptr};
    std::unique_ptr<SDL_Event> event_{nullptr};
};
