#include "sprite.h"

#include "graphics.h"

Sprite::Sprite(Graphics& graphics,
               const std::string& file_path,
               int src_x,
               int src_y,
               int width,
               int height)
    : sprite_sheet_(graphics.loadImage(file_path)) {
  src_rect_.x = src_x;
  src_rect_.y = src_y;
  src_rect_.w = width;
  src_rect_.h = height;
}

void Sprite::draw(Graphics& graphics, int x, int y) {
  graphics.blitSurface(sprite_sheet_, &src_rect_, x, y);
}
