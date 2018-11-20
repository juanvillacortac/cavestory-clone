#ifndef BAT_H_
#define BAT_H_

#include "units.h"
#include "rectangle.h"
#include "sprite_state.h"
#include "floating_number.h"
#include "damageable.h"

struct Graphics;
struct Sprite;
struct SDL_Rect;

class Bat : public Damageable {
	private:
		typedef std::tuple<HorizontalFacing> SpriteTuple;

		struct SpriteState : public SpriteTuple {
			SpriteState(const SpriteTuple& tuple) : SpriteTuple(tuple) {}
			HorizontalFacing horizontal_facing(const SpriteTuple& tuple) const { return std::get<0>(tuple); }
		};

		void initializeSprites(Graphics& graphics);
		void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);
		SpriteState getSpriteState() const;

		const units::Game flight_center_y_;

		bool alive_;

		units::Game x_, y_;

		std::shared_ptr<FloatingNumber> get_damage_text() { return damage_text_; };

		units::Degrees flight_angle_;

		HorizontalFacing facing_;

		std::map<SpriteState, std::shared_ptr<Sprite>> sprites_;

		std::shared_ptr<FloatingNumber> damage_text_;
	public:
		Bat(Graphics& graphics, units::Game x, units::Game y);

		units::HP contactDamage() const;

		bool update(units::MS elapsed_time_ms, units::Game player_x);
		void draw(Graphics& graphics, SDL_Rect& camera);

		Rectangle damageRectangle() const {
			return Rectangle(
					x_, y_ + units::kHalfTile,
					32, 0
					);
		}

		Rectangle collisionRectangle() const {
			return Rectangle(
					x_, y_,
					units::tileToGame(1), units::tileToGame(1)
					);
		}

		void takeDamage(units::HP damage)
		{ damage_text_->addValue(damage); alive_ = false;}

		units::Game center_x() const { return x_ + units::kHalfTile; }
		units::Game center_y() const { return y_ + units::kHalfTile; }
};

#endif // BAT_H_
