#ifndef POLAR_STAR_H_
#define POLAR_STAR_H_

#include "sprite_state.h"
#include "units.h"
#include "rectangle.h"
#include "projectile.h"

#include <vector>

struct Graphics;
struct Sprite;
struct Map;

class PolarStar {
	private:
		typedef std::tuple<HorizontalFacing, VerticalFacing> SpriteTuple;

		struct SpriteState : public SpriteTuple {
			SpriteState(const SpriteTuple& tuple) : SpriteTuple(tuple) {}
			HorizontalFacing horizontal_facing(const SpriteTuple& tuple) const { return std::get<0>(tuple); }
			VerticalFacing vertical_facing(const SpriteTuple& tuple) const { return std::get<1>(tuple); }
		};

		class Projectile : public ::Projectile {
			private:
				units::Game getX() const;
				units::Game getY() const;

				std::shared_ptr<Sprite> sprite_;

				const HorizontalFacing horizontal_direction_;
				const VerticalFacing vertical_direction_;

				const units::Game x_, y_;

				bool alive_;

				units::Game offset_;
			public:
				Projectile(std::shared_ptr<Sprite> sprite,
						HorizontalFacing horizontal_direction,
						VerticalFacing vertical_direction,
						units::Game x, units::Game y);

				// Returns true if |this| are alive.
				bool update(units::MS elapsed_time, const Map& map);

				void draw(Graphics& graphics);

				void collideWithEnemy() { alive_ = false; }

				Rectangle collisionRectangle() const;
				units::HP contactDamage() const { return 1; }
		};

		units::Game gun_x(HorizontalFacing horizontal_facing, units::Game player_x) const
		{ return horizontal_facing == LEFT ? player_x - units::kHalfTile : player_x; }

		units::Game gun_y(VerticalFacing vertical_facing, bool gun_up, units::Game player_y) const;

		void initializeSprites(Graphics& graphics);
		void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);

		std::map<SpriteState, std::shared_ptr<Sprite> > sprite_map_;

		std::shared_ptr<Sprite> horizontal_projectile_;
		std::shared_ptr<Sprite> vertical_projectile_;

		std::shared_ptr<Projectile> projectile_a_;
		std::shared_ptr<Projectile> projectile_b_;
	public:
		PolarStar(Graphics& graphics);

		void draw(
				Graphics& graphics,
				HorizontalFacing horizontal_facing, VerticalFacing vertical_facing,
				bool gun_up,
				units::Game x, units::Game y);

		void startFire(units::Game player_x, units::Game player_y,
				HorizontalFacing horizontal_facing, VerticalFacing vertical_facing,
				bool gun_up);

		void stopFire() {}

		void updateProjectiles(units::MS elapsed_time_ms, const Map& map);

		std::vector<std::shared_ptr< ::Projectile>> getProjectiles();
};

#endif // POLAR_STAR_H_
