#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
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

  SDL_Surface *pb = SDL_CreateRGBSurface(0, APP_SIZE, 8, 0, 0, 0, 0);
  if (pb == NULL) {
    THROW("buffer surface init failed")
    return 3;
  }

  if (BX_ReadPalette(pb->format->palette, "4col.palt")) {
    THROW("pallete read failed")
    return 4;
  }

  BX_Geometry rgeom;
  BX_Geometry wgeom;
  BX_Mat3 rotm;
  /*
   = {{57513, 0, 31419},
                  {0, 65536, 0},
                  {
                      -31419,
                      0,
                      57513,
                  }};
  */
  if (BX_ReadGeometry(&rgeom, "2tri.geom")) {
    THROW("geometry read failed")
    return 5;
  }
  BX_CopyGeometry(&wgeom, &rgeom);

  Uint32 angle;
  for (angle = 0; angle < 90; angle++) {
    BX_SetRotYToMat3(&rotm, angle);
    BX_TransformGeometry(&wgeom, &rgeom, &rotm);
    SDL_LockSurface(pb);
    BX_DrawGeometry(pb, &wgeom);
    SDL_UnlockSurface(pb);
    SDL_UpperBlit(pb, NULL, SDL_GetWindowSurface(win), NULL);
    SDL_UpdateWindowSurface(win);
    SDL_Delay(100);
    SDL_FillRect(pb, NULL, 0);
  }

  SDL_Quit();

  return 0;
}