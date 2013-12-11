#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL/SDL.h>

#include <string>

using std::string;

class Graphics;

class Sprite {
 public:
  Sprite(const std::string& file_path,
         int src_x,
         int src_y,
         int width,
         int height);

  ~Sprite();

  void draw(Graphics& graphics, int x, int y);

 private:
  SDL_Surface* sprite_sheet_;
  SDL_Rect src_rect_;
};

#endif  // SPRITE_H_

