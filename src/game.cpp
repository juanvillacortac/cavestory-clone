#include "game.h"
#include "graphics.h"
#include "input.h"
#include "timer.h"
#include "player.h"
#include "bat.h"
#include "map.h"

#include <SDL/SDL.h>
#include <stdlib.h>
#include <time.h>

namespace {
	const units::FPS kFps = 60;
	const units::MS kMaxFrameTime = 5 * 1000 / kFps;
}

units::Tile Game::kScreenWidth = 20;
units::Tile Game::kScreenHeight = 15;

Game::Game() {
	srand(static_cast<unsigned int>(time(NULL)));

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

	player_.reset(new Player(graphics,
				units::tileToGame(kScreenWidth / 2),
				units::tileToGame(kScreenWidth / 2)
				));
	
	damage_texts_.addDamageable(player_);

	bat_.reset(new Bat(
				graphics,
				units::tileToGame(15),
				units::tileToGame((kScreenWidth / 2) - 3)
				));

	damage_texts_.addDamageable(bat_);

	map_.reset(Map::createTestMap(graphics));

	particle_.reset(new HeadBumpParticle(
				graphics,
				units::tileToGame(kScreenWidth) / 2,
				units::tileToGame(kScreenHeight) / 2
				));

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

		// Player Fire
		if (input.wasKeyPressed(SDLK_w)) {
			player_->startFire();
		}
		else if (input.wasKeyReleased(SDLK_w)) {
			player_->stopFire();
		}

		// Fullscreen
		if(input.wasKeyPressed(SDLK_F4)) {
			graphics.setVideo();
			player_.reset(new Player(
						graphics,
						units::tileToGame(kScreenWidth / 2),
						units::tileToGame(kScreenWidth / 2) - units::tileToPixel(4)
						));
		}

		// Reset game
		if(input.wasKeyPressed(SDLK_r)) {
			player_.reset(new Player(graphics, units::tileToGame(kScreenWidth / 2),
						units::tileToGame(kScreenWidth / 2) - units::tileToPixel(4)
						));
			damage_texts_.addDamageable(player_);
			bat_.reset(new Bat(
						graphics, units::tileToGame(15),
						units::tileToGame((kScreenWidth / 2) - 3)
					  ));
			damage_texts_.addDamageable(bat_);
		}

		const units::MS current_time_ms = SDL_GetTicks();
		const units::MS elapsed_time = current_time_ms - last_update_time;
		update(std::min(elapsed_time, kMaxFrameTime));
		last_update_time = current_time_ms;

		draw(graphics);

		const units::MS ms_per_frame = 1000 / kFps;
		const units::MS elapsed_time_ms = SDL_GetTicks() - start_time_ms;

		if(elapsed_time_ms < ms_per_frame)
			SDL_Delay(ms_per_frame - elapsed_time_ms);
	}
}

void Game::update(units::MS elapsed_time_ms) {
	Timer::updateAll(elapsed_time_ms);
	damage_texts_.update(elapsed_time_ms);
	particle_->update(elapsed_time_ms);
	player_->update(elapsed_time_ms, *map_);
	if(bat_) {
		if(!bat_->update(elapsed_time_ms, player_->center_x()))
			bat_.reset();
	}

	std::vector<std::shared_ptr<Projectile>> projectiles(player_->getProjectiles());
	
	for(size_t i = 0; i < projectiles.size(); i++) {
		if(bat_ && bat_->collisionRectangle().collideWith(projectiles[i]->collisionRectangle())) {
			bat_->takeDamage(projectiles[i]->contactDamage());
			projectiles[i]->collideWithEnemy();
		}
	}

	if(bat_ && bat_->damageRectangle().collideWith(player_->damageRectangle()))
		player_->takeDamage(bat_->contactDamage());
}

void Game::draw(Graphics& graphics) {
	graphics.clear();

	map_->drawBackground(graphics);
	if(bat_)
		bat_->draw(graphics);
	player_->draw(graphics);
	damage_texts_.draw(graphics);
	map_->draw(graphics);
	particle_->draw(graphics);

	player_->drawHUD(graphics);

	graphics.flip();
}
