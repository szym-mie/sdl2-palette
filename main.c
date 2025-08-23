#include <SDL2/SDL.h>

#include "def.h"

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
    
    *(bs->pixels + 200 + 0) = 1;
    *(bs->pixels + 200 + 1) = 1;
    *(bs->pixels + 200 + 2) = 1;
    *(bs->pixels + 200 + 3) = 1;
    *(bs->pixels + 200 + 4) = 1;
    *(bs->pixels + 200 + 5) = 1;
    *(bs->pixels + 200 + 6) = 1;
    *(bs->pixels + 200 + 7) = 1;

    *(bs->pixels + 400 + 0) = 2;
    *(bs->pixels + 400 + 1) = 1;
    *(bs->pixels + 400 + 2) = 2;
    *(bs->pixels + 400 + 3) = 1;
    *(bs->pixels + 400 + 4) = 2;
    *(bs->pixels + 400 + 5) = 1;
    *(bs->pixels + 400 + 6) = 2;
    *(bs->pixels + 400 + 7) = 1;

    *(bs->pixels + 600 + 0) = 2;
    *(bs->pixels + 600 + 1) = 2;
    *(bs->pixels + 600 + 2) = 2;
    *(bs->pixels + 600 + 3) = 2;
    *(bs->pixels + 600 + 4) = 2;
    *(bs->pixels + 600 + 5) = 2;
    *(bs->pixels + 600 + 6) = 2;
    *(bs->pixels + 600 + 7) = 2;

    *(bs->pixels + 800 + 0) = 3;
    *(bs->pixels + 800 + 1) = 2;
    *(bs->pixels + 800 + 2) = 3;
    *(bs->pixels + 800 + 3) = 2;
    *(bs->pixels + 800 + 4) = 3;
    *(bs->pixels + 800 + 5) = 2;
    *(bs->pixels + 800 + 6) = 3;
    *(bs->pixels + 800 + 7) = 2;

    SDL_UnlockSurface(bs);

    SDL_BlitSurface(bs, NULL, SDL_GetWindowSurface(win), NULL);
    SDL_UpdateWindowSurface(win);

    SDL_Delay(2000);

    SDL_Quit();

    return 0;
}