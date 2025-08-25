#include <SDL2/SDL.h>

#include "def.h"
#include "triangle.h"

void on_except(const char *where, const char *reason) {
    SDL_Log("EXCEPTION [%s] %s\n", where, reason);
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
    
    BX_Geometry geom;
    BX_ReadGeometry(&geom, "2tri.geom");
    BX_DrawGeometry(bs, &geom);

    SDL_UnlockSurface(bs);

    SDL_BlitSurface(bs, NULL, SDL_GetWindowSurface(win), NULL);
    SDL_UpdateWindowSurface(win);

    SDL_Delay(2000);

    SDL_Quit();

    return 0;
}