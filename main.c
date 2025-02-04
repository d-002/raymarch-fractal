#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <err.h>

#include "src/utils.h"
#include "src/complex.h"
#include "src/quaternion.h"
#include "src/distance_estimator.h"
#include "src/raymarch.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer;
SDL_Texture *pixBuf = NULL;

void init() {
    if (SDL_Init(SDL_INIT_VIDEO)) errx(1, "%s", SDL_GetError());

    window = SDL_CreateWindow("Raymarched fractals",
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

int checkClose(SDL_Event event) {
    switch (event.type) {
        case SDL_QUIT:
            return 1;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                return 1;
    }

    return 0;
}

int checkEvents(struct camera *cam) {
    SDL_Event event;

    const double movement = 0.1;
    const double rotation = 0.1;

    while (SDL_PollEvent(&event)) {
        if (checkClose(event)) return 1;

        if (event.type != SDL_KEYDOWN) continue;

        double c = cos(cam->rot[2]), s = sin(cam->rot[2]);
        switch(event.key.keysym.sym) {
            case SDLK_z:
                cam->pos.x -= movement*s;
                cam->pos.z -= movement*c;
                break;
            case SDLK_q:
                cam->pos.x -= movement*c;
                cam->pos.z += movement*s;
                break;
            case SDLK_s:
                cam->pos.x += movement*s;
                cam->pos.z += movement*c;
                break;
            case SDLK_d:
                cam->pos.x += movement*c;
                cam->pos.z -= movement*s;
                break;
            case SDLK_a:
                cam->pos.w -= movement;
                break;
            case SDLK_e:
                cam->pos.w += movement;
                break;
            case SDLK_SPACE:
                cam->pos.y += movement;
                break;
            case SDLK_LSHIFT:
                cam->pos.y -= movement;
                break;
            case SDLK_j:
                cam->rot[0] -= rotation;
                break;
            case SDLK_k:
                cam->rot[0] += rotation;
                break;
            case SDLK_UP:
                cam->rot[1] += rotation;
                break;
            case SDLK_DOWN:
                cam->rot[1] -= rotation;
                break;
            case SDLK_LEFT:
                cam->rot[2] += rotation;
                break;
            case SDLK_RIGHT:
                cam->rot[2] -= rotation;
                break;
            case SDLK_RETURN:
                res = res == 1 ? 4 : 1;
                aalias = aalias == 1 ? 2 : 1;
        }
    }

    return 0;
}

void mainloop() {
    SDL_Event event;

    // main loop, wait for the window to be closed
    double prev = tstamp(), now;

    while (1) {
        while (SDL_PollEvent(&event))
            if (checkClose(event)) break;

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

int main() {
    init();
    uint32_t *pixels = malloc(WIDTH * HEIGHT * sizeof(uint32_t));

    struct camera cam = {
        { -2, 0, 3, 0 },
        { 0, 0, 0 }
    };
    while (1) {
        renderScene(pixels, julia_de, &cam);
        updateScreen(pixels);

        if (checkEvents(&cam)) break;
    }

    free(pixels);

    quit();
    return 0;
}
