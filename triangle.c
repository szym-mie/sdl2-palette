#include "triangle.h"

int BX_ReadGeometry(BX_Geometry *geometry, const char *file) {
    SDL_RWops *ops = SDL_RWFromFile(file, "r");
    if (ops == NULL) return 1;
    Uint8 size = SDL_ReadU8(ops);
    if (size == 0 || size >= 192) return 2;
    geometry->size = size;
    Uint8 i;
    Uint8 j;
    for (i = 0; i < size; i++) {
        BX_Face *face = &geometry->faces[i];
        face->va.x = SDL_ReadLE32(ops);
        face->va.y = SDL_ReadLE32(ops);
        face->va.z = SDL_ReadLE32(ops);
        face->vb.x = SDL_ReadLE32(ops);
        face->vb.y = SDL_ReadLE32(ops);
        face->vb.z = SDL_ReadLE32(ops);
        face->vc.x = SDL_ReadLE32(ops);
        face->vc.y = SDL_ReadLE32(ops);
        face->vc.z = SDL_ReadLE32(ops);
        geometry->colors[i] = SDL_ReadU8(ops);
    }
    return 0;
}

void BX_MinusVec3(const BX_Vec3 *a, const BX_Vec3 *b, BX_Vec3 *c) {

}

Sint32 BX_GetEdgeRegion(const BX_Vec3 *p, const BX_Vec3 *u, const BX_Vec3 *v) {
    return (p->x - u->x) * (v->y - u->y) - (p->y - u->y) * (v->x - u->x);
}

#define DX(U, V) ((V).x - (U).x)
#define DY(U, V) ((V).y - (U).y)
#define EDGE(P, V, XD, YD) DX(V, P) * YD - DY(V, P) * XD

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))

void BX_DrawFace(SDL_Surface *surface, const BX_Face *face, BX_Color color) {
    Sint32 xl = MIN(MIN(face->va.x, face->vb.x), face->vc.x);
    Sint32 xu = MAX(MAX(face->va.x, face->vb.x), face->vc.x);
    Sint32 yl = MIN(MIN(face->va.y, face->vb.y), face->vc.y);
    Sint32 yu = MAX(MAX(face->va.y, face->vb.y), face->vc.y);
    BX_Vec3 vl = { xl, yl, 0 };

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

    for (y = yl; y <= yu; y++) {
        for (x = xl; x <= xu; x++) {
            if (erab < 0 || erbc < 0 || erca < 0) continue;
            *(pix + row + x) = color;
            erab += dyab;
            erbc += dybc;
            erca += dyca;
        }
        herab += dxab;
        herbc += dxbc;
        herca += dxca;
        erab = herab;
        erbc = herbc;
        erca = herca;
        row += pitch;
    }
}
