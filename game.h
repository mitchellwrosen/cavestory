#ifndef GAME_H_
#define GAME_H_

#include <boost/scoped_ptr.hpp>

class Graphics;
class Sprite;

class Game {
 public:
  Game();
  ~Game();

 private:
  void eventLoop();
  void update();
  void draw(Graphics& graphics);

  boost::scoped_ptr<Sprite> sprite_;
};

#endif  // GAME_H_