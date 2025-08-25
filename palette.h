#define _PALETTE_H_
#define _PALETTE_H_

#include <SDL2/SDL.h>

#include "io.h"

int BX_ReadPalette(SDL_Palette *palette, const char *file);

#endif /* _PALETTE_H_ */
