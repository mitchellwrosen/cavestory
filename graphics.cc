#include "graphics.h"

#include <SDL/SDL.h>

#include "sdl/sdl.h"

namespace {
const int kScreenWidth  = 640;
const int kScreenHeight = 480;
const int kBitsPerPixel = 32;
}

Graphics::Graphics() : screen_(sdl::setVideoMode(kScreenWidth, kScreenHeight, kBitsPerPixel, 0)) {
  sdl::disableCursor();
}

sdl::Surface* Graphics::loadImage(const string& file_path) {
  if (!sprite_sheets_.count(file_path))
    sprite_sheets_[file_path] = shared_ptr<sdl::Surface>(sdl::Surface::fromBmp(file_path.c_str()));
  return sprite_sheets_[file_path].get();
}

int Graphics::blitSurface(sdl::Surface* src, sdl::Rect* src_rect, int x, int y) {
  return sdl::blitSurface(src, src_rect, screen_.get(), x, y);
}

void Graphics::flip() {
  screen_->flip();
}

void Graphics::clear() {
  screen_->fillRect(NULL, 0);
}
