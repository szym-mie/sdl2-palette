#include "triangle.h"
#include "fixed.h"
#include "io.h"
#include <SDL2/SDL_stdinc.h>

#define DOT(U, V)                                                              \
  (SFIX32_MUL((U).x, (V).x) + SFIX32_MUL((U).y, (V).y) +                       \
   SFIX32_MUL((U).z, (V).z))

void BX_SetRotYToMat3(BX_Mat3 *m, Sint32 angle) {
  Sfix32 c = SFIX32_COS(angle);
  Sfix32 s = SFIX32_SIN(angle);
  m->rx.x = c;
  m->rx.y = 0;
  m->rx.z = s;
  m->ry.x = 0;
  m->ry.y = SFIX32(1, 0);
  m->ry.z = 0;
  m->rz.x = -s;
  m->rz.y = 0;
  m->rz.z = c;
}

void BX_TransformVec3(BX_Vec3 *vt, const BX_Vec3 *vs, const BX_Mat3 *m) {
  Sint32 x = DOT(*vs, m->rx);
  Sint32 y = DOT(*vs, m->ry);
  Sint32 z = DOT(*vs, m->rz);
  vt->x = x;
  vt->y = y;
  vt->z = z;
}

void BX_CopyVec3(BX_Vec3 *vt, const BX_Vec3 *vs) {
  vt->x = vs->x;
  vt->y = vs->y;
  vt->z = vs->z;
}

void BX_TransformGeometry(BX_Geometry *gt, BX_Geometry *gs, const BX_Mat3 *m) {
  Uint8 i;
  for (i = 0; i < gs->size; i++) {
    BX_TransformVec3(&gt->faces[i].va, &gs->faces[i].va, m);
    BX_TransformVec3(&gt->faces[i].vb, &gs->faces[i].vb, m);
    BX_TransformVec3(&gt->faces[i].vc, &gs->faces[i].vc, m);
  }
}

int BX_ReadGeometry(BX_Geometry *geometry, const char *file) {
  IO_Stream *io = IO_ReadStream(file);
  Uint8 size;
  if (io == NULL)
    return 1;
  IO_TRY(IO_ReadLiteral(io, "verts="), 2);
  IO_TRY(IO_ReadU8(io, &size), 2);
  if (size == 0 || size >= BX_MAX_FACES)
    return 2;
  geometry->size = size;
  Uint8 i;
  for (i = 0; i < size; i++) {
    BX_Face *face = &geometry->faces[i];
    IO_TRY(IO_SkipSpace(io), 3);
    IO_TRY(IO_ReadS32(io, &face->va.x), 3);
    IO_TRY(IO_SkipSpace(io), 3);
    IO_TRY(IO_ReadS32(io, &face->va.y), 3);
    IO_TRY(IO_SkipSpace(io), 3);
    IO_TRY(IO_ReadS32(io, &face->va.z), 3);
    IO_TRY(IO_SkipSpace(io), 3);
    IO_TRY(IO_ReadS32(io, &face->vb.x), 3);
    IO_TRY(IO_SkipSpace(io), 3);
    IO_TRY(IO_ReadS32(io, &face->vb.y), 3);
    IO_TRY(IO_SkipSpace(io), 3);
    IO_TRY(IO_ReadS32(io, &face->vb.z), 3);
    IO_TRY(IO_SkipSpace(io), 3);
    IO_TRY(IO_ReadS32(io, &face->vc.x), 3);
    IO_TRY(IO_SkipSpace(io), 3);
    IO_TRY(IO_ReadS32(io, &face->vc.y), 3);
    IO_TRY(IO_SkipSpace(io), 3);
    IO_TRY(IO_ReadS32(io, &face->vc.z), 3);
    IO_TRY(IO_SkipSpace(io), 3);
    IO_TRY(IO_ReadU8(io, &geometry->colors[i]), 3);
  }
  IO_QuitStream(io);
  return 0;
}

void BX_CopyGeometry(BX_Geometry *gt, BX_Geometry *gs) {
  Uint8 i;
  gt->size = gs->size;
  for (i = 0; i < gs->size; i++) {
    BX_CopyVec3(&gt->faces[i].va, &gs->faces[i].va);
    BX_CopyVec3(&gt->faces[i].vb, &gs->faces[i].vb);
    BX_CopyVec3(&gt->faces[i].vc, &gs->faces[i].vc);
    gt->colors[i] = gs->colors[i];
  }
}

Sint32 BX_GetEdgeRegion(const BX_Vec3 *p, const BX_Vec3 *u, const BX_Vec3 *v) {
  return (p->x - u->x) * (v->y - u->y) - (p->y - u->y) * (v->x - u->x);
}

#define DX(U, V) ((V).x - (U).x)
#define DY(U, V) ((V).y - (U).y)
#define EDGE(P, V, XD, YD) DX(V, P) * YD - DY(V, P) * XD

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))

void BX_DrawGeometry(SDL_Surface *surface, const BX_Geometry *geometry) {
  Uint8 i;
  for (i = 0; i < geometry->size; i++)
    BX_DrawFace(surface, &geometry->faces[i], geometry->colors[i]);
}

void BX_DrawFace(SDL_Surface *surface, const BX_Face *face, BX_Color color) {
  Sint32 xl = MIN(MIN(face->va.x, face->vb.x), face->vc.x);
  Sint32 xu = MAX(MAX(face->va.x, face->vb.x), face->vc.x);
  Sint32 yl = MIN(MIN(face->va.y, face->vb.y), face->vc.y);
  Sint32 yu = MAX(MAX(face->va.y, face->vb.y), face->vc.y);
  BX_Vec3 vl = {xl, yl, 0};

  Sint32 dxab = DX(face->va, face->vb);
  Sint32 dyab = DY(face->va, face->vb);
  Sint32 dxbc = DX(face->vb, face->vc);
  Sint32 dybc = DY(face->vb, face->vc);
  Sint32 dxca = DX(face->vc, face->va);
  Sint32 dyca = DY(face->vc, face->va);

  Sint32 erab = EDGE(vl, face->va, dxab, dyab);
  Sint32 erbc = EDGE(vl, face->vb, dxbc, dybc);
  Sint32 erca = EDGE(vl, face->vc, dxca, dyca);
  Sint32 herab = erab;
  Sint32 herbc = erbc;
  Sint32 herca = erca;

  Uint8 *pix = surface->pixels;
  Uint32 pitch = surface->w;
  Uint32 row = pitch * yl;
  Sint32 x, y;

  // IO_Log("f %p\n", face);
  // IO_Log("dx %d %d %d\n", dxab, dxbc, dxca);
  // IO_Log("dy %d %d %d\n", dyab, dybc, dyca);
  for (y = yl; y <= yu; y++) {
    // IO_Log("%d %d %d\n", erab, erbc, erca);
    for (x = xl; x <= xu; x++) {
      if (erab >= 0 && erbc >= 0 && erca >= 0)
        *(pix + row + x) = color;
      erab += dyab;
      erbc += dybc;
      erca += dyca;
    }
    herab -= dxab;
    herbc -= dxbc;
    herca -= dxca;
    erab = herab;
    erbc = herbc;
    erca = herca;
    row += pitch;
  }
}
