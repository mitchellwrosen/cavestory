#include "player.h"

#include <cmath>
#include <boost/shared_ptr.hpp>

#include "animated_sprite.h"
#include "game.h"
#include "graphics.h"

using boost::shared_ptr;
using std::max;
using std::min;

namespace {
const float kMaxVelocityX        = 0.325f;   // pixels/ms
const float kSlowdownFactor      = 0.8f;
const float kWalkingAcceleration = 0.0012f;  // pixels/ms/ms
}

bool operator<(const Player::SpriteState& a, const Player::SpriteState& b) {
  if (a.motion_type != b.motion_type)
    return a.motion_type < b.motion_type;
  if (a.facing != b.facing)
    return a.facing < b.facing;
  return false;
}

Player::Player(Graphics& graphics, int x, int y)
    : x_(x)
    , y_(y)
    , vel_x_(0.0f)
    , vel_y_(0.0f)
    , acc_x_(0.0f)
    , acc_y_(0.0f)
    , facing_(LEFT)
    {
  initializeSprites(graphics);
}

void Player::update(int elapsed_time_ms) {
  sprites_[getSpriteState()]->update(elapsed_time_ms);

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
  sprites_[getSpriteState()]->draw(graphics, x_, y_);
}

void Player::startMovingLeft() {
  acc_x_ = -kWalkingAcceleration;
  facing_ = LEFT;
}

void Player::startMovingRight() {
  acc_x_ = kWalkingAcceleration;
  facing_ = RIGHT;
}

void Player::stopMoving() {
  acc_x_ = 0.0f;
}

void Player::initializeSprites(Graphics& graphics) {
  sprites_[SpriteState(STANDING, LEFT)] = shared_ptr<Sprite>(new Sprite(
      graphics,
      "char.bmp",
      0,
      0,
      Game::kTileSize,
      Game::kTileSize)
  );

  sprites_[SpriteState(WALKING, LEFT)] = shared_ptr<Sprite>(new AnimatedSprite(
      graphics,
      "char.bmp",
      0,
      0,
      Game::kTileSize,
      Game::kTileSize,
      15,
      3)
  );

  sprites_[SpriteState(STANDING, RIGHT)] = shared_ptr<Sprite>(new Sprite(
      graphics,
      "char.bmp",
      0,
      Game::kTileSize,
      Game::kTileSize,
      Game::kTileSize)
  );

  sprites_[SpriteState(WALKING, RIGHT)] = shared_ptr<Sprite>(new AnimatedSprite(
      graphics,
      "char.bmp",
      0,
      Game::kTileSize,
      Game::kTileSize,
      Game::kTileSize,
      15,
      3)
  );
}

Player::SpriteState Player::getSpriteState() {
  return SpriteState(
      acc_x_ == 0.0f ? STANDING : WALKING,
      facing_
  );
}
