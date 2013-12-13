#include "sdl/sdl.h"

#include <SDL/SDL.h>

#include "sdl/surface.h"

namespace sdl {

int init(Uint32 flags) {
  return SDL_Init(flags);
}

void quit() {
  SDL_Quit();
}

uint32_t getTicks() {
  return SDL_GetTicks();
}

void delay(uint32_t ms) {
  SDL_Delay(ms);
}

void enableCursor() {
  SDL_ShowCursor(SDL_ENABLE);
}

void disableCursor() {
  SDL_ShowCursor(SDL_DISABLE);
}

Surface setVideoMode(int width, int height, int bpp, Uint32 flags) {
  return Surface(SDL_SetVideoMode(width, height, bpp, flags));
}

int blitSurface(Surface& src, SDL_Rect* src_rect, Surface& dst, int x, int y) {
  SDL_Rect dst_rect;
  dst_rect.x = x;
  dst_rect.y = y;
  return SDL_BlitSurface(src.get(), src_rect, dst.get(), &dst_rect);
}

}  // namespace sdl
