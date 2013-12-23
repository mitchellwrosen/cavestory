#include "game.h"

#include <boost/bind.hpp>

#include "animated_sprite.h"
#include "input.h"
#include "graphics.h"
#include "player.h"
#include "sdl/sdl.h"
#include "sprite.h"

namespace {
const int kFps = 60;
}

Game::Game() {
  sdl::init(SDL_INIT_EVERYTHING);

  eventLoop();
}

Game::~Game() {
  sdl::quit();
}

void Game::eventLoop() {
  Graphics graphics;

  player_.reset(new Player(graphics, 325, 240));

  bool running = true;
  int last_update_time = sdl::getTicks();
  while (running) {
    const int start_time_ms = sdl::getTicks();

    running = handleInput();

    const int current_time_ms = sdl::getTicks();
    update(current_time_ms - last_update_time);
    last_update_time = current_time_ms;

    draw(graphics);

    const int elapsed_time_ms = sdl::getTicks() - start_time_ms;
    sdl::delay(1000/kFps - elapsed_time_ms);
  }
}

bool Game::handleInput() {
  input_.beginNewFrame();

  sdl::Event event;
  while (sdl::pollEvent(&event)) {
    switch (event.type) {
      case sdl::event::keydown:
        input_.keyDown(event.key.keysym.sym);
        break;
      case sdl::event::keyup:
        input_.keyUp(event.key.keysym.sym);
        break;
      default:
        break;
    }
  }

  if (input_.pressed(SDLK_ESCAPE))
    return false;

  player_->handleInput(input_);

  return true;
}

void Game::update(int elapsed_time_ms) {
  player_->update(elapsed_time_ms);
}

void Game::draw(Graphics& graphics) {
  graphics.clear();
  player_->draw(graphics);
  graphics.flip();
}
