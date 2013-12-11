#include "sprite.h"

#include <SDL/SDL.h>

#include "graphics.h"

Sprite::Sprite(const std::string& file_path,
         int src_x,
         int src_y,
         int width,
         int height) {
  sprite_sheet_ = SDL_LoadBMP(file_path.c_str());

  src_rect_.x = src_x;
  src_rect_.y = src_y;
  src_rect_.w = width;
  src_rect_.y = height;
}

Sprite::~Sprite() {
  SDL_FreeSurface(sprite_sheet_);
}

void Sprite::draw(Graphics& graphics, int x, int y) {
  graphics.blitSurface(sprite_sheet_, &src_rect_, x, y);
}
