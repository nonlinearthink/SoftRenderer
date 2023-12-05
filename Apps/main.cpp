#define SDL_MAIN_HANDLED

#include "framework.hpp"

int main(int argc, char* argv[]) {
    const int width = 640;
    const int height = 480;

    auto app = RenderApplication::CreateApplication(width, height);
    if (app == nullptr) {
        return 1;
    }

    while (app->running) {
        app->Tick();
    }

    return 0;
}
