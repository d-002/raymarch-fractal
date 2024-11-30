#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <err.h>

#include "src/utils.h"
#include "src/quaternion.h"
#include "src/distance_estimator.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer;
SDL_Texture *pixBuf = NULL;

void init() {
    if (SDL_Init(SDL_INIT_VIDEO)) errx(1, "%s", SDL_GetError());

    window = SDL_CreateWindow("Filter",
                              SDL_WINDOWPOS_CENTERED,
                              0,
                              WIDTH,
                              HEIGHT,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window) errx(1, "no window: %s", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) errx(1, "no renderer: %s", SDL_GetError());

    pixBuf = SDL_CreateTexture(renderer,
                               SDL_PIXELFORMAT_RGBA32,
                               SDL_TEXTUREACCESS_STATIC,
                               WIDTH,
                               HEIGHT);
    if (!pixBuf) errx(1, "no pixbuf: %s", SDL_GetError());
}

void mainloop() {
    SDL_Event event;

    // main loop, wait for the window to be closed
    int running = 1;
    double prev = tstamp(), now;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) running = 0;
                    break;
            }
            if (!running) break;
        }

        // limit framerate
        now = tstamp();
        float to_wait = 1.0/FPS - now + prev;
        if (to_wait > 0) usleep(to_wait*1e6);
        prev = tstamp();
    }
}

void quit() {
    SDL_DestroyTexture(pixBuf);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderScene() {
}

int main() {
    init();

    renderScene();

    mainloop();
    quit();
    return 0;
}
