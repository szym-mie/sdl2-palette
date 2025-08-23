#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <SDL2/SDL.h>

#include "def.h"

void on_except(const char *where, const char *reason) {
    printf("EXCEPTION [%s] %s\n", where, reason);
}

#define THROW(REASON) on_except("main", REASON);

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        THROW("video init failed")
        return 1;
    }

	SDL_Window* win = SDL_CreateWindow(APP_TITLE, APP_POS, APP_SIZE, APP_OPTS);
    if (win == NULL) {
        THROW("window init failed")
        return 2;
    }

    SDL_Surface* bs = SDL_CreateRGBSurface(0, APP_SIZE, 8, 0, 0, 0, 0);
    if (bs == NULL) {
        THROW("buffer surface init failed")
        return 3;
    }

    SDL_Color cpal[4] = {
        { .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff },
        { .r = 0xe0, .g = 0x00, .b = 0x00, .a = 0xff },
        { .r = 0xb0, .g = 0x00, .b = 0x00, .a = 0xff },
        { .r = 0x80, .g = 0x00, .b = 0x00, .a = 0xff }
    };
    SDL_SetPaletteColors(bs->format->palette, cpal, 0, 4);

    SDL_LockSurface(bs);
    
    uint8_t *pix = bs->pixels; 

    *(pix + 200 + 0) = 1;
    *(pix + 200 + 1) = 1;
    *(pix + 200 + 2) = 1;
    *(pix + 200 + 3) = 1;
    *(pix + 200 + 4) = 1;
    *(pix + 200 + 5) = 1;
    *(pix + 200 + 6) = 1;
    *(pix + 200 + 7) = 1;

    *(pix + 400 + 0) = 2;
    *(pix + 400 + 1) = 1;
    *(pix + 400 + 2) = 2;
    *(pix + 400 + 3) = 1;
    *(pix + 400 + 4) = 2;
    *(pix + 400 + 5) = 1;
    *(pix + 400 + 6) = 2;
    *(pix + 400 + 7) = 1;

    *(pix + 600 + 0) = 2;
    *(pix + 600 + 1) = 2;
    *(pix + 600 + 2) = 2;
    *(pix + 600 + 3) = 2;
    *(pix + 600 + 4) = 2;
    *(pix + 600 + 5) = 2;
    *(pix + 600 + 6) = 2;
    *(pix + 600 + 7) = 2;

    *(pix + 800 + 0) = 3;
    *(pix + 800 + 1) = 2;
    *(pix + 800 + 2) = 3;
    *(pix + 800 + 3) = 2;
    *(pix + 800 + 4) = 3;
    *(pix + 800 + 5) = 2;
    *(pix + 800 + 6) = 3;
    *(pix + 800 + 7) = 2;

    SDL_UnlockSurface(bs);

    SDL_BlitSurface(bs, NULL, SDL_GetWindowSurface(win), NULL);
    SDL_UpdateWindowSurface(win);

    SDL_Delay(2000);

    SDL_Quit();

    return 0;
}