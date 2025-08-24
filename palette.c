#include "palette.h"

int BX_ReadPalette(SDL_Palette *palette, const char *file) {
    SDL_RWops *ops = SDL_RWFromFile(file, "r");
    if (ops == NULL) return 1;
    SDL_Color cols[256];
    SDL_Color *col;
    Uint8 i;
    for (i = 0;; i++) {
        col = &cols[i];
        Uint8 r = SDL_ReadU8(ops);
        Uint8 g = SDL_ReadU8(ops);
        Uint8 b = SDL_ReadU8(ops);
        if (r == 0 || g == 0 || b == 0) return 2;
        col->r = r;
        col->g = g;
        col->b = b;
        col->a = 0xff;
        if (i == 255) return 0;
    }
    SDL_SetPaletteColors(palette, cols, 256);
}
