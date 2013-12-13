#ifndef SDL_SURFACE_H_
#define SDL_SURFACE_H_

#include <string>

#include "sdl/sdl.h"

using std::string;

namespace sdl {

class Surface {
 public:
  Surface();
  explicit Surface(SDL_Surface* surface);

  ~Surface();

  static Surface fromBmp(const string& filename);

  int flip();
  int fillRect(Rect* dst_rect, Uint32 color);

  SDL_Surface* get() const { return surface_; }

 private:
  SDL_Surface* surface_;
};

}  // namespace sdl

#endif  // SDL_SURFACE_H_
