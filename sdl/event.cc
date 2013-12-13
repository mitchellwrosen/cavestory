#include "sdl/event.h"

#include <SDL/SDL.h>

namespace sdl {

int pollEvent(Event* event) { 
  return SDL_PollEvent(event);
}

}  // namespace sdl
