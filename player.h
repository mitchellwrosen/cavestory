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

  void lookUp();
  void lookDown();
  void lookHorizontal();

  void startJump();
  void stopJump();

 private:
  struct SpriteState;

  enum Motion {
    FIRST_MOTION,
    STANDING = FIRST_MOTION,
    WALKING,
    JUMPING,
    FALLING,
    LAST_MOTION
  };

  enum HFacing {
    FIRST_HFACING,
    LEFT = FIRST_HFACING,
    RIGHT,
    LAST_HFACING
  };

  enum VFacing {
    FIRST_VFACING,
    UP = FIRST_VFACING,
    DOWN,
    HORIZONTAL,
    LAST_VFACING
  };

  struct SpriteState {
    SpriteState(Motion motion, HFacing hfacing, VFacing vfacing)
        : motion(motion), hfacing(hfacing), vfacing(vfacing) {
    }

    bool operator<(const SpriteState& other) const {
      if (motion != other.motion)
        return motion < other.motion;
      if (hfacing != other.hfacing)
        return hfacing < other.hfacing;
      if (vfacing != other.vfacing)
        return vfacing < other.vfacing;
      return false;
    }

    bool standing()         const { return motion == STANDING;    }
    bool walking()          const { return motion == WALKING;     }
    bool jumping()          const { return motion == JUMPING;     }
    bool falling()          const { return motion == FALLING;     }
    bool facingLeft()       const { return hfacing == LEFT;       }
    bool facingRight()      const { return hfacing == RIGHT;      }
    bool facingUp()         const { return vfacing == UP;         }
    bool facingDown()       const { return vfacing == DOWN;       }
    bool facingHorizontal() const { return vfacing == HORIZONTAL; }

    Motion motion;
    HFacing hfacing;
    VFacing vfacing;
  };

  void initializeSprites(Graphics& graphics);
  void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);
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

  int jump_time_remaining_;
  bool jump_active_;
  bool on_ground_;

  Motion motion_;
  HFacing hfacing_;
  VFacing vfacing_;

  map<SpriteState, shared_ptr<Sprite> > sprites_;
};

#endif  // PLAYER_H_
