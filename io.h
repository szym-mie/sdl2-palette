#ifndef _IO_H_
#define _IO_H_

#include <SDL2/SDL.h>

typedef SDL_RWops IO_Stream;

#define IO_Log SDL_Log

#define IO_TRY(OPER, EXCEPT) if (OPER) return EXCEPT

IO_Stream *IO_ReadStream(const char *file);
int IO_SkipSpace(IO_Stream *stream);
int IO_ReadLiteral(IO_Stream *stream, char *literal);
int IO_ReadU8(IO_Stream *stream, Uint8 *value);
int IO_ReadS32(IO_Stream *stream, Sint32 *value);
Sint32 IO_Offset(IO_Stream *stream);
int IO_QuitStream(IO_Stream *stream);

#endif /* _IO_H_ */