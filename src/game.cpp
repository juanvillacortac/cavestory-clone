#include <SDL/SDL.h>
#include "game.h"
#include "graphics.h"
#include "sprite.h"
#include "animated_spr.h"

namespace {
	const int kFps = 60;
}

int Game::kTileSize = 32;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_ShowCursor(SDL_DISABLE);

	eventLoop();
}

Game::~Game() {
	SDL_Quit();
}

void Game::eventLoop() {
	bool running = true;

	Graphics graphics;
	SDL_Event event;

	sprite_.reset(new Animated_spr(
				"assets/MyChar.bmp", 0, 32, kTileSize, kTileSize, 15, 3));

	int last_update_time = SDL_GetTicks();

	while(running) {
		const int start_time_ms = SDL_GetTicks();
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE) {
						running = false;
					}
					break;
				default:
					break;
			}
		}

		const int current_time_ms = SDL_GetTicks();
		update(current_time_ms - last_update_time);
		last_update_time = current_time_ms;
		draw(graphics);
		
		const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;

		SDL_Delay(1000/*ms*/ / kFps - elapsed_time_ms/*ms*/);
	}
}

void Game::update(int elapsed_time_ms) {
	sprite_->update(elapsed_time_ms);
}

void Game::draw(Graphics& graphics) {
	sprite_->draw(graphics, 320, 240);
	graphics.flip();
}
