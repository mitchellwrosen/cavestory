#include "animated_sprite.h"

#include "game.h"
#include "sprite.h"

AnimatedSprite::AnimatedSprite(
    Graphics& graphics,
    const string& file_path,
    int src_x,
    int src_y,
    int width,
    int height,
    int fps,
    int num_frames) :
  Sprite(graphics, file_path, src_x, src_y, width, height),
  frame_time_(1000/fps),
  num_frames_(num_frames),
  current_frame_(0),
  elapsed_time_(0) {
}


AnimatedSprite::~AnimatedSprite() {
}

void AnimatedSprite::update(int elapsed_time_ms) {
  elapsed_time_ += elapsed_time_ms;
  if (elapsed_time_ > frame_time_) {
    ++current_frame_;
    elapsed_time_ = 0;

    if (current_frame_ < num_frames_) {
      src_rect_.x += Game::kTileSize;
    } else {
      src_rect_.x -= (num_frames_ - 1) * Game::kTileSize;
      current_frame_ = 0;
    }
  }
}
