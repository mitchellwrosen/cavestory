#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL/SDL.h>
#include <string>

using std::string;

class Graphics;

namespace sdl {
class Surface;
}  // namespace sdl

class Sprite {
 public:
  Sprite(Graphics& graphics,
         const string& file_path,
         int src_x,
         int src_y,
         int width,
         int height);

  virtual ~Sprite();

  virtual void update(int) {};
  void draw(Graphics& graphics, int x, int y);

 protected:
  SDL_Rect src_rect_;

 private:
  sdl::Surface& sprite_sheet_;
};

#endif  // SPRITE_H_

