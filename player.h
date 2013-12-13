#ifndef PLAYER_H_
#define PLAYER_H_

#include <boost/scoped_ptr.hpp>

using boost::scoped_ptr;

class Graphics;
class Sprite;

class Player {
 public:
  Player(Graphics& graphics, int x, int y);

  void update(int elapsed_time_ms);
  void draw(Graphics& graphics);

  void startMovingLeft();
  void startMovingRight();
  void stopMoving();

 private:
  int x_;
  int y_;

  float vel_x_;
  float vel_y_;

  float acc_x_;
  float acc_y_;

  scoped_ptr<Sprite> sprite_;
};

#endif  // PLAYER_H_
