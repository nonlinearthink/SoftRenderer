#define SDL_MAIN_HANDLED

#include <iostream>

#include "SDL.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVENTS) < 0) {
        SDL_Log("SDL init failed");
        return 1;
    }

    const int wWidth = 640;
    const int wHeight = 480;

    SDL_Window* window = SDL_CreateWindow(
        "SoftRenderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        wWidth, wHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("create window failed");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        SDL_Log("create renderer failed");
        SDL_Quit();
        return 1;
    }

    bool isQuit = false;
    SDL_Event event;
    while (!isQuit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isQuit = true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
