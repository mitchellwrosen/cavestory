#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <string>

#include "sdl/sdl.h"

using boost::shared_ptr;
using boost::scoped_ptr;
using std::map;
using std::string;

class Graphics {
 public:
  Graphics();

  sdl::Surface* loadImage(const string& file_path);

  int blitSurface(sdl::Surface* src, sdl::Rect* src_rect, int x, int y);

  void flip();
  void clear();

 private:
  map<string, shared_ptr<sdl::Surface> > sprite_sheets_;

  scoped_ptr<sdl::Surface> screen_;
};

#endif  // GRAPHICS_H_
