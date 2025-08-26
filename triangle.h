#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>

#include "io.h"

#define BX_MAX_FACES 192

typedef struct {
  Sint32 x;
  Sint32 y;
  Sint32 z;
} BX_Vec3;

typedef struct {
  BX_Vec3 rx;
  BX_Vec3 ry;
  BX_Vec3 rz;
} BX_Mat3;

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

void BX_SetRotYToMat3(BX_Mat3 *m, Sint32 angle);
void BX_TransformVec3(BX_Vec3 *vt, const BX_Vec3 *vs, const BX_Mat3 *m);
void BX_CopyVec3(BX_Vec3 *vt, const BX_Vec3 *vs);
void BX_TransformGeometry(BX_Geometry *gt, BX_Geometry *gs, const BX_Mat3 *m);
int BX_ReadGeometry(BX_Geometry *geometry, const char *file);
void BX_CopyGeometry(BX_Geometry *gt, BX_Geometry *gs);
void BX_DrawGeometry(SDL_Surface *surface, const BX_Geometry *geometry);
void BX_DrawFace(SDL_Surface *surface, const BX_Face *face, BX_Color color);

#endif /* _TRIANGLE_H_ */
