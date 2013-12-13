#include "input.h"

void Input::beginNewFrame() {
  pressed_keys_.clear();
  released_keys_.clear();
}

void Input::keyUp(const SDLKey& key) {
  released_keys_[key] = true;
  held_keys_[key] = false;
}

void Input::keyDown(const SDLKey& key) {
  pressed_keys_[key] = true;
  held_keys_[key] = true;
}

bool Input::pressed(SDLKey key) {
  return pressed_keys_[key];
}

bool Input::released(SDLKey key) {
  return released_keys_[key];
}

bool Input::held(SDLKey key) {
  return held_keys_[key];
}
