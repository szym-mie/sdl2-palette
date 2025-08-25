#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <SDL2/SDL.h>

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
    BX_Face faces[192];
    BX_Color colors[192];
    Uint32 size;
} BX_Geometry;

int BX_ReadGeometry(BX_Geometry *geometry, const char *file);
void BX_DrawFace(SDL_Surface *surface, const BX_Face *face, BX_Color color);

#endif /* _TRIANGLE_H_ */
