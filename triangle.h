#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <SDL2/SDL.h>

#include "io.h"

#define BX_MAX_FACES 192

typedef struct {
  Sint32 x;
  Sint32 y;
  Sint32 z;
} BX_Vec3;

typedef struct {
  BX_Vec3 va;
  BX_Vec3 vb;
  BX_Vec3 vc;
} BX_Face;

typedef Uint8 BX_Color;

typedef struct {
  BX_Face faces[BX_MAX_FACES];
  BX_Color colors[BX_MAX_FACES];
  Uint32 size;
} BX_Geometry;

int BX_ReadGeometry(BX_Geometry *geometry, const char *file);
void BX_DrawGeometry(SDL_Surface *surface, const BX_Geometry *geometry);
void BX_DrawFace(SDL_Surface *surface, const BX_Face *face, BX_Color color);

#endif /* _TRIANGLE_H_ */
