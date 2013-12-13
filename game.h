#ifndef GAME_H_
#define GAME_H_

#include <boost/scoped_ptr.hpp>

#include "input.h"
#include "sdl/sdl.h"

using boost::scoped_ptr;

class Graphics;
class Player;

class Game {
 public:
  Game();
  ~Game();

  static const int kTileSize;

 private:
  void eventLoop();

  void updateInput();

  void update(int elapsed_time_ms);
  void draw(Graphics& graphics);

  Input input_;
  scoped_ptr<Player> player_;
};

#endif  // GAME_H_
