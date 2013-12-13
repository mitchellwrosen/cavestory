#ifndef INPUT_H_
#define INPUT_H_

#include <map>
#include <SDL/SDL.h>

using std::map;

class Input {
 public:
  void beginNewFrame();

  void keyUp(const SDLKey& key);
  void keyDown(const SDLKey& key);

  bool pressed(SDLKey key);
  bool released(SDLKey key);
  bool held(SDLKey key);

 private:
  map<SDLKey, bool> held_keys_;
  map<SDLKey, bool> pressed_keys_;
  map<SDLKey, bool> released_keys_;
};

#endif  // INPUT_H_

