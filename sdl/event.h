#ifndef SDL_EVENT_H_
#define SDL_EVENT_H_

#include <SDL/SDL.h>

namespace sdl {

namespace event {
const Uint8 keydown = SDL_KEYDOWN;
const Uint8 keyup   = SDL_KEYUP;
}  // namespace event

typedef SDL_Event Event;
typedef void (*EventHandler)(const Event&);

int pollEvent(Event* event);

}  // namespace sdl

#endif  // SDL_EVENT_H_
