#include "palette.h"

int BX_ReadPalette(SDL_Palette *palette, const char *file) {
    IO_Stream *io = IO_ReadStream(file);
    if (io == NULL) return 1;
    SDL_Color cols[256];
    SDL_Color *col;
    Uint8 i;
    for (i = 0;; i++) {
        col = &cols[i];
        if (IO_ReadU8(io, &col->r)) return 2;
        if (IO_ReadU8(io, &col->g)) return 2;
        if (IO_ReadU8(io, &col->b)) return 2;
        col->a = 0xff;
        if (i == 255) break;
        if (IO_SkipSpace(io)) return 2;
    }
    SDL_SetPaletteColors(palette, cols, 256);
    IO_QuitStream(io);
    return 0;
}
