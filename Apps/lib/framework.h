#include <memory>

#include "SDL.h"
#include "SoftRenderer.h"

struct SDL_Window_Deleter {
    void operator()(SDL_Window* window) const { SDL_DestroyWindow(window); }
};
// Define the smart pointer of SDL_Window
using SDL_Window_Ptr = std::unique_ptr<SDL_Window, SDL_Window_Deleter>;

struct SDL_Surface_Deleter {
    void operator()(SDL_Surface* surface) const { SDL_FreeSurface(surface); }
};
// Define the smart pointer of SDL_Surface
using SDL_Surface_Ptr = std::unique_ptr<SDL_Surface, SDL_Surface_Deleter>;

/**
 * @brief Base Class for All Application
 *
 * Used to wrap the interface of the SDL library
 */
class RenderApplication {
public:
    int width, height;

    RenderApplication(int _width, int _height);
    ~RenderApplication();

    bool Initialize();
    void Run();

    virtual void Render(){};

protected:
    std::unique_ptr<SoftRenderer::Renderer> _renderer;
    SDL_Window_Ptr _window;
    SDL_Surface_Ptr _window_surface;
    std::unique_ptr<SDL_Event> _event;
};
