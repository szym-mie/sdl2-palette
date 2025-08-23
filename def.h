#ifndef _DEF_H_
#define _DEF_H_

#include <SDL2/SDL.h>

typedef void (*on_except_t)(const char *where, const char *reason);

#define APP_VER_MAJOR "0"
#define APP_VER_MINOR "1"
#define APP_VER APP_VER_MAJOR "." APP_VER_MINOR
#define APP_TITLE "BX" " - " APP_VER

#define APP_POS 0, 0
#define APP_SIZE 200, 420
#define APP_OPTS (SDL_WINDOW_BORDERLESS | SDL_WINDOW_INPUT_GRABBED)

#endif /* _DEF_H_ */
