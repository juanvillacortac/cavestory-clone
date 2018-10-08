#include "game.h"
#include "graphics.h"
#include "timer.h"
#include "player.h"
#include "bat.h"
#include "map.h"
#include "death_cloud_particle.h"

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

	Input input;

	eventLoop();
}

Game::~Game() {
	SDL_Quit();
}

void Game::eventLoop() {
	bool running = true;

	Graphics graphics;
	SDL_Event event;

	ParticleTools particle_tools = {
		front_particle_system_,
		entity_particle_system_,
		graphics
	};

	player_.reset(new Player(
				graphics,
				particle_tools,
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
				case SDL_JOYBUTTONDOWN:
					input.joyButtonDownEvent(event);
					break;
				case SDL_JOYBUTTONUP:
					input.joyButtonUpEvent(event);
					break;
				case SDL_JOYAXISMOTION:
					input.joyAxisEvent(event);
				default:
					break;
			}
		}

		if (input.wasKeyPressed(SDLK_ESCAPE)) {
			running = false;
		}

		// Player movement
		if (input.isKeyHeld(SDLK_LEFT) && input.isKeyHeld(SDLK_RIGHT)) {
			player_->stopMoving();
		}
		else if (input.isKeyHeld(SDLK_LEFT) || input.getJoyAxis(0) < -8000) {
			player_->startMovingLeft();
		}
		else if (input.isKeyHeld(SDLK_RIGHT) || input.getJoyAxis(0) > 8000) {
			player_->startMovingRight();
		}
		else {
			player_->stopMoving();
		}

		// Looking
		if (input.isKeyHeld(SDLK_UP) && input.isKeyHeld(SDLK_DOWN)) {
			player_->lookHorizontal();
		}
		else if (input.isKeyHeld(SDLK_UP) || input.getJoyAxis(1) < -8000) {
			player_->lookUp();
		}
		else if (input.isKeyHeld(SDLK_DOWN) || input.getJoyAxis(1) > 8000) {
			player_->lookDown();
		} else {
			player_->lookHorizontal();
		}

		// Player Jump
		if (input.wasKeyPressed(SDLK_q) || input.wasJoyButtonPressed(0)) {
			player_->startJump();
		}
		else if (input.wasKeyReleased(SDLK_q) || input.wasJoyButtonReleased(0)){
			player_->stopJump();
		}

		// Player Fire
		if (input.wasKeyPressed(SDLK_w) || input.wasJoyButtonPressed(1)) {
			player_->startFire();
		}
		else if (input.wasKeyReleased(SDLK_w) || input.wasJoyButtonReleased(1)) {
			player_->stopFire();
		}

		// Fullscreen
		if (input.wasKeyPressed(SDLK_F4)) {
			graphics.setVideo();
			player_.reset(new Player(
						graphics,
						particle_tools,
						units::tileToGame(kScreenWidth / 2),
						units::tileToGame(kScreenWidth / 2) - units::tileToPixel(4)
						));
			damage_texts_.addDamageable(player_);
		}

		// Reset game
		if (input.wasKeyPressed(SDLK_r) || input.wasJoyButtonPressed(3)) {
			player_.reset(new Player(
						graphics,
						particle_tools,
						units::tileToGame(kScreenWidth / 2),
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
		update(std::min(elapsed_time, kMaxFrameTime), graphics);
		last_update_time = current_time_ms;

		draw(graphics);

		const units::MS ms_per_frame = 1000 / kFps;
		const units::MS elapsed_time_ms = SDL_GetTicks() - start_time_ms;

		if (elapsed_time_ms < ms_per_frame)
			SDL_Delay(ms_per_frame - elapsed_time_ms);
	}
}

void Game::update(units::MS elapsed_time_ms, Graphics& graphics) {
	Timer::updateAll(elapsed_time_ms);

	damage_texts_.update(elapsed_time_ms);

	front_particle_system_.update(elapsed_time_ms);
	entity_particle_system_.update(elapsed_time_ms);

	player_->update(elapsed_time_ms, *map_);

	if (bat_) {
		if (!bat_->update(elapsed_time_ms, player_->center_x())) {
			ParticleTools particle_tools = {
				front_particle_system_,
				entity_particle_system_,
				graphics
			};
			DeathCloudParticle::createRandomDeathClouds(particle_tools,
					bat_->center_x(), bat_->center_y(),
					3);
			bat_.reset();
		}
	}

	std::vector<std::shared_ptr<Projectile>> projectiles(player_->getProjectiles());
	
	for (size_t i = 0; i < projectiles.size(); i++) {
		if (bat_ && bat_->collisionRectangle().collideWith(projectiles[i]->collisionRectangle())) {
			bat_->takeDamage(projectiles[i]->contactDamage());
			projectiles[i]->collideWithEnemy();
		}
	}

	if (bat_ && bat_->damageRectangle().collideWith(player_->damageRectangle()))
		player_->takeDamage(bat_->contactDamage());
}

void Game::draw(Graphics& graphics) {
	graphics.clear();

	map_->drawBackground(graphics);
	if (bat_)
		bat_->draw(graphics);
	entity_particle_system_.draw(graphics);
	player_->draw(graphics);
	damage_texts_.draw(graphics);
	map_->draw(graphics);
	front_particle_system_.draw(graphics);

	player_->drawHUD(graphics);

	graphics.flip();
}
