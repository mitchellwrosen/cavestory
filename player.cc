#include "player.h"

#include <cmath>
#include <boost/shared_ptr.hpp>

#include "animated_sprite.h"
#include "game.h"
#include "graphics.h"
#include "sprite_constants.h"

using boost::shared_ptr;
using std::max;
using std::min;

namespace {
const float kGravity        = 0.0012f;  // pixels/ms/ms
const int   kJumpTime       = 275;      // ms
const float kJumpVel        = 0.325f;   // pixels/ms
const float kMaxVelX        = 0.325f;   // pixels/ms
const float kMaxVelY        = 0.325f;   // pixels/ms
const float kSlowdownFactor = 0.8f;     // unitless
const float kWalkingAcc     = 0.0012f;  // pixels/ms/ms
}

Player::Player(Graphics& graphics, int x, int y)
    : x_(x)
    , y_(y)
    , vel_x_(0.0f)
    , vel_y_(0.0f)
    , acc_x_(0.0f)
    , acc_y_(0.0f)
    , jump_time_remaining_(0)
    , jump_active_(false)
    , on_ground_(false)
    , motion_(STANDING)
    , hfacing_(LEFT)
    , vfacing_(HORIZONTAL)
    {
  initializeSprites(graphics);
}

void Player::handleInput(const Input& input) {
  if ((input.held(sdl::key::left) && input.held(sdl::key::right)) ||
      (!input.held(sdl::key::left) && !input.held(sdl::key::right)))
    stopMoving();
  else if (input.held(sdl::key::left))
    startMovingLeft();
  else
    startMovingRight();

  if ((input.held(sdl::key::up) && input.held(sdl::key::down)) ||
      (!input.held(sdl::key::up) && !input.held(sdl::key::down)))
    lookHorizontal();
  else if (input.held(sdl::key::up))
    lookUp();
  else
    lookDown();


  if (input.pressed(sdl::key::z))
    startJump();
  else if (input.released(sdl::key::z))
    stopJump();
}

void Player::startMovingLeft() {
  acc_x_ = -kWalkingAcc;
  hfacing_ = LEFT;
}

void Player::startMovingRight() {
  acc_x_ = kWalkingAcc;
  hfacing_ = RIGHT;
}

void Player::stopMoving() {
  acc_x_ = 0.0f;
}

void Player::lookUp() {
  vfacing_ = UP;
}

void Player::lookDown() {
  vfacing_ = DOWN;
}

void Player::lookHorizontal() {
  vfacing_ = HORIZONTAL;
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
  for (Motion motion = FIRST_MOTION; motion < LAST_MOTION; ++motion) {
    for (HFacing hfacing = FIRST_HFACING; hfacing < LAST_HFACING; ++hfacing) {
      for (VFacing vfacing = FIRST_VFACING; vfacing < LAST_VFACING; ++vfacing)
        initializeSprite(graphics, SpriteState(motion, hfacing, vfacing));
    }
  }
}

void Player::initializeSprite(Graphics& graphics, const SpriteState& sprite_state) {
  int x;
  if (sprite_state.walking()) {
    x = sprite::kWalkX;
  } else {
    if (sprite_state.facingDown()) {
      x = sprite_state.standing() ?  sprite::kBackX : sprite::kDownX;
    } else {
      if (sprite_state.standing())
        x = sprite::kStandX;
      if (sprite_state.jumping())
        x = sprite::kJumpX;
      if (sprite_state.falling())
        x = sprite::kFallX;
    }
  }

  if (sprite_state.facingUp())
    x += sprite::kUpOffsetX;

  int y = sprite_state.facingLeft() ? sprite::kLeftY : sprite::kRightY;

  Sprite* sprite;
  if (sprite_state.motion == WALKING) {
    sprite = new AnimatedSprite(
        graphics,
        sprite::kFilePath,
        x,
        y,
        sprite::kTileSize,
        sprite::kTileSize,
        15,
        3);
  } else {
    sprite = new Sprite(
        graphics,
        sprite::kFilePath,
        x,
        y,
        sprite::kTileSize,
        sprite::kTileSize);
  }

  sprites_[sprite_state] = shared_ptr<Sprite>(sprite);
}

Player::SpriteState Player::getSpriteState() {
  Motion motion;
  if (isOnGround())
    motion = acc_x_ == 0.0f ? STANDING : WALKING;
  else
    motion = vel_y_ < 0.0f ? JUMPING : FALLING;
  return SpriteState(motion, hfacing_, vfacing_);
}

void Player::jumpReset() {
  jump_time_remaining_ = kJumpTime;
  jumpReactivate();
}

void Player::update(int elapsed_time) {
  shared_ptr<Sprite> sprite = sprites_[getSpriteState()];

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
