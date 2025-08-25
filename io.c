#include "io.h"

IO_Stream *IO_ReadStream(const char *file) {
    IO_Stream *stream = SDL_RWFromFile(file, "r");
    if (stream == NULL) {
        IO_Log("IO_ReadStream: cannot open\n");
        return NULL;
    }
    return stream;
}

int IO_SkipSpace(IO_Stream *stream) {
    char c = SDL_ReadU8(stream);
    if (c == '\0') {
        IO_Log("IO_SkipSpace: EOF at pos %d\n", IO_Offset(stream));
        return 1;
    }
    int is_space = c == ' ' || c == ',' || c == '\n';
    if (!is_space) {
        IO_Log("IO_SkipSpace: not a spc/nl at pos %d\n", IO_Offset(stream));
        return 2;
    }
    return 0;
}

int IO_ReadLiteral(IO_Stream *stream, char *literal) {
    char *t;
    for (t = literal; *t != '\0'; t++) {
        char c = SDL_ReadU8(stream);
        if (c == '\0')  {
            IO_Log("IO_ReadLiteral: EOF at pos %d\n", IO_Offset(stream));
            return 1;
        }
        if (*t != c) {
            IO_Log("IO_ReadLiteral: bad char at pos %d\n", IO_Offset(stream));
            return 2;
        }
    }
    return 0;
}

#define IS_DIGIT(C) (C >= '0' && C <= '9')
#define IS_HEXAL(C) (C >= 'a' && C <= 'f')
#define IS_HEX(C) IS_DIGIT(C) || IS_HEXAL(C)
#define TO_HEX(C) (IS_DIGIT(C) ? (C - '0') : IS_HEXAL(C) ? (C - 'a' + 0xa) : 0)

int IO_ReadU8(IO_Stream *stream, Uint8 *value) {
    char cu = SDL_ReadU8(stream);
    if (cu == '\0') {
        IO_Log("IO_ReadU8: EOF at pos %d\n", IO_Offset(stream));
        return 1;
    }
    char cl = SDL_ReadU8(stream);
    if (cl == '\0') {
        IO_Log("IO_ReadU8: EOF at pos %d\n", IO_Offset(stream));
        return 1;
    }
    if (!IS_HEX(cu) || !IS_HEX(cl)) {
        IO_Log("IO_ReadU8: bad hex at pos %d\n", IO_Offset(stream));
        return 2;
    }
    *value = (TO_HEX(cu) << 4) | TO_HEX(cl);
    return 0;
}

int IO_ReadS32(IO_Stream *stream, Sint32 *value) {
    Uint8 b3, b2, b1, b0;
    int st;
    st = IO_ReadU8(stream, &b3);
    if (st)
        return st;
    st = IO_ReadU8(stream, &b2);
    if (st)
        return st;
    st = IO_ReadU8(stream, &b1);
    if (st)
        return st;
    st = IO_ReadU8(stream, &b0);
    if (st)
        return st;
    *value = (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
    return 0;
}

Sint32 IO_Offset(IO_Stream *stream) {
    return SDL_RWtell(stream);
}

int IO_QuitStream(IO_Stream *stream) {
    return SDL_RWclose(stream);
}