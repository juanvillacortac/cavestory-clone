#ifndef PLAYER_H_
#define PLAYER_H_

#include "sprite.h"
#include "sprite_state.h"
#include "rectangle.h"
#include "units.h"
#include "kinematics.h"
#include "map_collidable.h"
#include "varying_width_spr.h"
#include "number_spr.h"
#include "damage_text.h"
#include "damageable.h"
#include "timer.h"
#include "polar_star.h"
#include "hud_experience.h"

#include <cassert>

struct Graphics;
struct Map;
struct Projectile;
struct ParticleTools;

class Player : public Damageable,
	private MapCollidable {
	private:
		enum MotionType {
			FIRST_MOTION_TYPE,
			STANDING = FIRST_MOTION_TYPE,
			INTERACTING,
			WALKING,
			JUMPING,
			FALLING,
			LAST_MOTION_TYPE
		};

		enum StrideType {
			FIRST_STRIDE_TYPE,
			STRIDE_MIDDLE = FIRST_STRIDE_TYPE,
			STRIDE_LEFT,
			STRIDE_RIGHT,
			LAST_STRIDE_TYPE
		};

		typedef std::tuple<MotionType, HorizontalFacing, VerticalFacing, StrideType> SpriteTuple;

		struct SpriteState : public SpriteTuple {
			SpriteState(const SpriteTuple& tuple) : SpriteTuple(tuple) {}

			MotionType motion_type(const SpriteTuple& tuple) const { return std::get<0>(tuple); }
			HorizontalFacing horizontal_facing(const SpriteTuple& tuple) const { return std::get<1>(tuple); }
			VerticalFacing vertical_facing(const SpriteTuple& tuple) const { return std::get<2>(tuple); }
			StrideType stride_type(const SpriteTuple& tuple) const { return std::get<3>(tuple); }
		};

		class WalkingAnimation {
			private:
				Timer frame_timer_;
				units::Frame current_frame_;

				bool forward_;
			public:
				WalkingAnimation();

				void update();
				void reset();

				StrideType stride() const;
		};

		class Health {
			private:
				units::HP damage_;
				Timer damage_timer_;

				units::HP max_health_;
				units::HP current_health_;

				Sprite health_bar_sprite_;
				VaryingWidthSprite health_fill_sprite_;
				VaryingWidthSprite damage_fill_sprite_;
			public:
				Health(Graphics& graphics);

				void update();
				void draw(Graphics& graphics);

				// returns true if we have died.
				bool takeDamage(units::HP damage);
		};

		MotionType motionType() const;

		VerticalFacing vertical_facing() const {
			return on_ground() && intended_vertical_facing_ == DOWN ?
				HORIZONTAL : intended_vertical_facing_;
		}

		bool on_ground() const { return on_ground_; }
		bool gun_up() const
		{ return motionType() == WALKING && walking_animation_.stride() != STRIDE_MIDDLE; }
		bool on_ground_;
		bool jump_active_;
		bool interacting_;

		Health health_;
		Timer invincible_timer_;
		PolarStar polar_star_;

		ExperienceHUD gun_experience_hud_;

		std::shared_ptr<DamageText> damage_text_;


		WalkingAnimation walking_animation_;

		bool spriteIsVisible() const;

		void initializeSprites(Graphics& graphics);
		void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);
		SpriteState getSpriteState();

		void updateX(units::MS elapsed_time_ms, const Map& map);
		void updateY(units::MS elapsed_time_ms, const Map& map);

		void onCollision(MapCollidable::SideType side, bool is_delta_direction);
		void onDelta(MapCollidable::SideType side);

		ParticleTools& particle_tools_;

		Kinematics kinematics_x_, kinematics_y_;
		int acceleration_x_;

		HorizontalFacing horizontal_facing_;
		VerticalFacing intended_vertical_facing_;

		std::map<SpriteState, std::shared_ptr<Sprite>> sprites_;

		std::unique_ptr<Sprite> health_bar_sprite_;
		std::unique_ptr<Sprite> health_fill_sprite_;

		std::unique_ptr<NumberSpr> health_number_sprite_;
	public:
		Player(Graphics& graphics, ParticleTools& particle_tools, units::Game x, units::Game y);

		void update(units::MS elapsed_time_ms, const Map& map);
		void draw(Graphics& graphics);

		void startMovingLeft();
		void startMovingRight();
		void stopMoving();

		void startJump();
		void stopJump();

		void lookUp();
		void lookDown();
		void lookHorizontal();

		void startFire();
		void stopFire();

		void takeDamage(units::HP damage);

		void drawHUD(Graphics& graphics);

		Rectangle damageRectangle() const;

		units::Game center_x() const { return kinematics_x_.position + units::kHalfTile; }
		units::Game center_y() const { return kinematics_y_.position + units::kHalfTile; }

		std::shared_ptr<DamageText> get_damage_text() { return damage_text_; };

		std::vector<std::shared_ptr<Projectile>> getProjectiles()
		{ return polar_star_.getProjectiles(); }
};

#endif // PLAYER_H_
