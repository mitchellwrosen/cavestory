#ifndef SDL_SDL_H_
#define SDL_SDL_H_

// Re-exports
#include "sdl/event.h"
#include "sdl/key.h"
#include "sdl/rect.h"
#include "sdl/surface.h"

#include <SDL/SDL.h>

#include "stdint.h"

namespace sdl {

class Surface;

int init(Uint32 flags);
void quit();

uint32_t getTicks();
void delay(uint32_t ms);

void enableCursor();
void disableCursor();

Surface* setVideoMode(int width, int height, int bpp, Uint32 flags);

int blitSurface(Surface* src, SDL_Rect* src_rect, Surface* dst, int x, int y);

}  // namespace sdl

#endif  // SDL_SDL_H_
