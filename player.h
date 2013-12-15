#ifndef PLAYER_H_
#define PLAYER_H_

#include <boost/shared_ptr.hpp>
#include <map>

#include "input.h"

using boost::shared_ptr;
using std::map;

class Graphics;
class Sprite;

class Player {
 public:
  Player(Graphics& graphics, int x, int y);

  void handleInput(const Input& input);
  void update(int elapsed_time_ms);
  void draw(Graphics& graphics);

  void startMovingLeft();
  void startMovingRight();
  void stopMoving();

  void startJump();
  void stopJump();

 private:
  enum MotionType {
    STANDING,
    WALKING,
  };

  enum Facing {
    LEFT,
    RIGHT,
  };

  struct SpriteState {
    SpriteState(MotionType motion_type = STANDING,
                Facing facing = LEFT) :
      motion_type(motion_type),
      facing(facing) {
    }

    MotionType motion_type;
    Facing facing;
  };

  friend bool operator<(const SpriteState& a, const SpriteState& b);

  void initializeSprites(Graphics& graphics);
  SpriteState getSpriteState();

  void jumpReset();
  void jumpReactivate() { jump_active_ = jump_time_remaining_ > 0; }
  void jumpDeactivate() { jump_active_ = false; }

  bool isOnGround() const { return on_ground_; }
  bool isMidJump() const { return vel_y_ < 0.0f; }

  int x_;
  int y_;
  float vel_x_;
  float vel_y_;
  float acc_x_;
  float acc_y_;

  bool on_ground_;

  int jump_time_remaining_;
  bool jump_active_;

  Facing facing_;

  map<SpriteState, shared_ptr<Sprite> > sprites_;
};

#endif  // PLAYER_H_
