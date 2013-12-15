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

  bool held(SDLKey key)     const { return held_keys_.count(key)     && held_keys_.at(key);     }
  bool pressed(SDLKey key)  const { return pressed_keys_.count(key)  && pressed_keys_.at(key);  }
  bool released(SDLKey key) const { return released_keys_.count(key) && released_keys_.at(key); }

 private:
  map<SDLKey, bool> held_keys_;
  map<SDLKey, bool> pressed_keys_;
  map<SDLKey, bool> released_keys_;
};

#endif  // INPUT_H_

