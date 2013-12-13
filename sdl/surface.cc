#include "sdl/surface.h"

#include <string>

using std::string;

namespace sdl {

Surface::Surface() : surface_(NULL) {
}

Surface::Surface(SDL_Surface* surface) : surface_(surface) {
}

Surface::~Surface() {
  if (surface_)
    SDL_FreeSurface(surface_);
}

// static
Surface Surface::fromBmp(const string& filename) {
  return Surface(SDL_LoadBMP(filename.c_str()));
}

int Surface::flip() {
  return SDL_Flip(surface_);
}

int Surface::fillRect(SDL_Rect* dst_rect, Uint32 color) {
  return SDL_FillRect(surface_, dst_rect, color);
}


}  // namespace sdl
