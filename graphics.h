#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <map>
#include <string>

#include "sdl/sdl.h"

using std::map;
using std::string;

class Graphics {
 public:
  Graphics();

  sdl::Surface& loadImage(const string& file_path);

  int blitSurface(sdl::Surface& src, sdl::Rect* src_rect, int x, int y);

  void flip();
  void clear();

 private:
  map<string, sdl::Surface> sprite_sheets_;

  sdl::Surface screen_;
};

#endif  // GRAPHICS_H_
