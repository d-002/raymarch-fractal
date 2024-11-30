#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <err.h>

#include "src/utils.h"
#include "src/complex.h"
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

void updateScreen(uint32_t *pixels) {
    SDL_UpdateTexture(pixBuf, NULL, pixels, WIDTH*sizeof(uint32_t));
    SDL_RenderCopy(renderer, pixBuf, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void quit() {
    SDL_DestroyTexture(pixBuf);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderScene() {
    uint32_t *pixels = malloc(WIDTH * HEIGHT * sizeof(uint32_t));

    // test 2D mandelbrot display

    int w2 = WIDTH/2, h2 = HEIGHT/2;
    double mult = 0.01;
    complex pos = { -0.5, 0 };

    for (int x = 0; x < WIDTH; x++)
        for (int y = 0; y < HEIGHT; y++) {
            quat q = { 0, 0, (x-w2) * mult + pos.real, (y-h2) * mult + pos.imag };

            float d = julia_de(&q);
            uint8_t col = d*255;

            pixels[y*WIDTH + x] = col * 0x10101;
        }

    updateScreen(pixels);

    free(pixels);
}

int main() {
    init();

    renderScene();

    mainloop();
    quit();
    return 0;
}
