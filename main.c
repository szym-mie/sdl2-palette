#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>

#include "def.h"
#include "palette.h"
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

  SDL_Window *win = SDL_CreateWindow(APP_TITLE, APP_POS, APP_SIZE, APP_OPTS);
  if (win == NULL) {
    THROW("window init failed")
    return 2;
  }

  SDL_Surface *bs = SDL_CreateRGBSurface(0, APP_SIZE, 8, 0, 0, 0, 0);
  if (bs == NULL) {
    THROW("buffer surface init failed")
    return 3;
  }

  if (BX_ReadPalette(bs->format->palette, "4col.palt")) {
    THROW("pallete read failed")
    return 4;
  }

  BX_Geometry geom;
  if (BX_ReadGeometry(&geom, "2tri.geom")) {
    THROW("geometry read failed")
    return 5;
  }

  SDL_LockSurface(bs);
  BX_DrawGeometry(bs, &geom);
  SDL_UnlockSurface(bs);

  SDL_UpperBlit(bs, NULL, SDL_GetWindowSurface(win), NULL);
  SDL_UpdateWindowSurface(win);

  SDL_Delay(2000);

  SDL_Quit();

  return 0;
}