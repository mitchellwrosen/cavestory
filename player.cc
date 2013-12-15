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
const float kGravity        = 0.0012f;  // pixels/ms/ms
const float kJumpVel        = 0.325f;   // pixels/ms
const int   kJumpTime       = 275;      // ms
const float kMaxVelX        = 0.325f;   // pixels/ms
const float kMaxVelY        = 0.325f;   // pixels/ms
const float kSlowdownFactor = 0.8f;     // unitless
const float kWalkingAcc     = 0.0012f;  // pixels/ms/ms
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
    , on_ground_(false)
    , jump_time_remaining_(0)
    , jump_active_(false)
    , facing_(LEFT)
    {
  initializeSprites(graphics);
}

void Player::handleInput(const Input& input) {
  if ((input.held(sdl::key::left) && input.held(sdl::key::right)) ||
      (!input.held(sdl::key::left) && !input.held(sdl::key::right))) {
    stopMoving();
  } else if (input.held(sdl::key::left)) {
    startMovingLeft();
  } else {
    startMovingRight();
  }

  if (input.pressed(sdl::key::z))
    startJump();
  else if (input.released(sdl::key::z))
    stopJump();
}

void Player::startMovingLeft() {
  acc_x_ = -kWalkingAcc;
  facing_ = LEFT;
}

void Player::startMovingRight() {
  acc_x_ = kWalkingAcc;
  facing_ = RIGHT;
}

void Player::stopMoving() {
  acc_x_ = 0.0f;
}

void Player::startJump() {
  if (isOnGround()) {
    jumpReset();
    vel_y_ = -kJumpVel;
  } else if (isMidJump()) {
    jumpReactivate();
  }
}

void Player::stopJump() {
  jumpDeactivate();
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

void Player::jumpReset() {
  jump_time_remaining_ = kJumpTime;
  jumpReactivate();
}

void Player::update(int elapsed_time) {
  sprites_[getSpriteState()]->update(elapsed_time);

  if (jump_active_) {
    jump_time_remaining_ -= elapsed_time;
    if (jump_time_remaining_ <= 0)
      jump_active_ = false;
  }

  x_ += round(vel_x_ * elapsed_time);

  vel_x_ += acc_x_ * elapsed_time;
  if (acc_x_ < 0.0f)
    vel_x_ = max(vel_x_, -kMaxVelX);
  else if (acc_x_ > 0.0f)
    vel_x_ = min(vel_x_, kMaxVelX);
  else if (on_ground_)
    vel_x_ *= kSlowdownFactor;

  y_ += round(vel_y_ * elapsed_time);
  if (!jump_active_)
    vel_y_ += min(vel_y_ + kGravity * elapsed_time, kMaxVelY);

  // TODO remove this hack
  if (y_ >= 320) {
    y_ = 320;
    vel_y_ = 0.0f;
  }
  on_ground_ = y_ == 320;
  // TODO remove this hack
}

void Player::draw(Graphics& graphics) {
  sprites_[getSpriteState()]->draw(graphics, x_, y_);
}
