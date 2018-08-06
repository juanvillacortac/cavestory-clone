#include <SDL/SDL.h>
#include "game.h"
#include "graphics.h"
#include "player.h"
#include "input.h"
#include "map.h"

namespace {
	const units::FPS kFps = 60;
}

int Game::kTileSize = 32;
int Game::kScreenWidth = 20 * Game::kTileSize;
int Game::kScreenHeight = 15 * Game::kTileSize;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);

	eventLoop();
}

Game::~Game() {
	SDL_Quit();
}

void Game::eventLoop() {
	bool running = true;

	Input input;
	Graphics graphics;
	SDL_Event event;

	player_.reset(new Player(graphics, Game::kScreenWidth / 2, Game::kScreenWidth / 2));

	map_.reset(Map::createTestMap(graphics));

	units::MS last_update_time = SDL_GetTicks();

	while(running) {
		const units::MS start_time_ms = SDL_GetTicks();

		input.beginNewFrame();

		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					input.keyDownEvent(event);
					break;
				case SDL_KEYUP:
					input.keyUpEvent(event);
					break;
				default:
					break;
			}
		}

		if(input.wasKeyPressed(SDLK_ESCAPE)) {
			running = false;
		}

		// Player movement
		if(input.isKeyHeld(SDLK_LEFT) && input.isKeyHeld(SDLK_RIGHT)) {
			player_->stopMoving();
		}
		else if(input.isKeyHeld(SDLK_LEFT)) {
			player_->startMovingLeft();
		}
		else if(input.isKeyHeld(SDLK_RIGHT)) {
			player_->startMovingRight();
		}
		else {
			player_->stopMoving();
		}

		// Looking
		if(input.isKeyHeld(SDLK_UP) && input.isKeyHeld(SDLK_DOWN)) {
			player_->lookHorizontal();
		}
		else if(input.isKeyHeld(SDLK_UP)) {
			player_->lookUp();
		}
		else if(input.isKeyHeld(SDLK_DOWN)) {
			player_->lookDown();
		} else {
			player_->lookHorizontal();
		}

		// Player Jump
		if(input.wasKeyPressed(SDLK_q)) {
			player_->startJump();
		}
		else if(input.wasKeyReleased(SDLK_q)){
			player_->stopJump();
		}

		// TODO: Fullscreen shit
		/*if(input.wasKeyPressed(SDLK_F4)) {
			graphics.setFullscreen();
		}*/

		const units::MS current_time_ms = SDL_GetTicks();
		update(current_time_ms - last_update_time);
		last_update_time = current_time_ms;
		draw(graphics);

		const units::MS ms_per_frame = 1000 / kFps;
		const units::MS elapsed_time_ms = SDL_GetTicks() - start_time_ms;

		if(elapsed_time_ms < ms_per_frame)
			SDL_Delay(ms_per_frame - elapsed_time_ms);
	}
}

void Game::update(units::MS elapsed_time_ms) {
	player_->update(elapsed_time_ms, *map_);
	map_->update(elapsed_time_ms);
}

void Game::draw(Graphics& graphics) {
	graphics.clear();
	map_->drawBackground(graphics);
	player_->draw(graphics);
	map_->draw(graphics);
	graphics.flip();
}
