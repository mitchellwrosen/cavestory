#include "player.h"

#include <cmath>
#include <boost/scoped_ptr.hpp>

#include "animated_sprite.h"
#include "game.h"
#include "graphics.h"

using std::max;
using std::min;

namespace {
const float kMaxVelocityX        = 0.325f;   // pixels/ms
const float kSlowdownFactor      = 0.8f;
const float kWalkingAcceleration = 0.0012f;  // pixels/ms/ms
}

Player::Player(Graphics& graphics, int x, int y)
    : x_(x)
    , y_(y)
    , vel_x_(0.0f)
    , vel_y_(0.0f)
    , acc_x_(0.0f)
    , acc_y_(0.0f)
    {
  sprite_.reset(new AnimatedSprite(
      graphics,
      "char.bmp",
      0,
      0,
      Game::kTileSize,
      Game::kTileSize,
      15,
      3)
  );

}

void Player::update(int elapsed_time_ms) {
  sprite_->update(elapsed_time_ms);

  x_ += round(vel_x_ * elapsed_time_ms);

  vel_x_ += acc_x_ * elapsed_time_ms;
  if (acc_x_ < 0.0f)
    vel_x_ = max(vel_x_, -kMaxVelocityX);
  else if (acc_x_ > 0.0f)
    vel_x_ = min(vel_x_, kMaxVelocityX);
  else
    vel_x_ *= kSlowdownFactor;
}

void Player::draw(Graphics& graphics) {
  sprite_->draw(graphics, x_, y_);
}

void Player::startMovingLeft() {
  acc_x_ = -kWalkingAcceleration;
}

void Player::startMovingRight() {
  acc_x_ = kWalkingAcceleration;
}

void Player::stopMoving() {
  acc_x_ = 0.0f;
}

