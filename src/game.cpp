#include <SDL/SDL.h>
#include "game.h"
#include "graphics.h"
#include "sprite.h"

namespace {
	const int kFps = 60;
}

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

	sprite_.reset(new Sprite(
				"assets/MyChar.bmp", 0, 0, 32, 32));

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

		update();
		draw(graphics);
		
		const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;

		SDL_Delay(1000/*ms*/ / kFps - elapsed_time_ms/*ms*/);
	}
}

void Game::update() {

}

void Game::draw(Graphics& graphics) {
	sprite_->draw(graphics, 320, 240);
	graphics.flip();
}
