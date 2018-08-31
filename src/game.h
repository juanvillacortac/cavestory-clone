#ifndef GAME_H_
#define GAME_H_

#include "units.h"
#include "damage_texts.h"
#include "particle_system.h"

#include <memory>

struct Graphics;
struct Player;
struct Bat;
struct Map;
struct ExperienceHUD;

class Game {
	private:
		void eventLoop();
		void update(units::MS elapsed_time_ms, Graphics& graphics);
		void draw(Graphics& graphics);

		std::shared_ptr<Player> player_;
		std::shared_ptr<Bat> bat_;
		std::unique_ptr<Map> map_;
		std::unique_ptr<ExperienceHUD> hud_;

		ParticleSystem front_particle_system_, entity_particle_system_;

		DamageTexts damage_texts_;
	public:
		Game();
		~Game();

		static units::Tile kScreenWidth;
		static units::Tile kScreenHeight;
};

#endif // GAME_H_
