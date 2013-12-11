#include "graphics.h"

#include <SDL/SDL.h>

namespace {
const int kScreenWidth = 640;
const int kScreenHeight = 480;
const int kBitsPerPixel = 32;
}

Graphics::Graphics() {
  screen_ = SDL_SetVideoMode(kScreenWidth, 
                             kScreenHeight, 
                             kBitsPerPixel, 
                             SDL_FULLSCREEN);
}

Graphics::~Graphics() {
  SDL_FreeSurface(screen_);
}

void Graphics::blitSurface(SDL_Surface* src, SDL_Rect* src_rect, int x, int y) {
  SDL_Rect dst_rect;
  dst_rect.x = x;
  dst_rect.y = y;
  SDL_BlitSurface(src, src_rect, screen_, &dst_rect);
}

void Graphics::flip() {
  SDL_Flip(screen_);
}
