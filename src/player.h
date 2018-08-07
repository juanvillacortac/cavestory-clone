#ifndef PLAYER_H_
#define PLAYER_H_

#include "sprite.h"
#include "rectangle.h"
#include "units.h"

//#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <map>

struct Sprite;
struct Graphics;
struct Map;

class Player {
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
		enum HorizontalFacing {
			FIRST_HORIZONTAL_FACING,
			LEFT = FIRST_HORIZONTAL_FACING,
			RIGHT,
			LAST_HORIZONTAL_FACING
		};
		enum VerticalFacing {
			FIRST_VERTICAL_FACING,
			UP = FIRST_VERTICAL_FACING,
			DOWN,
			HORIZONTAL,
			LAST_VERTICAL_FACING
		};

		struct SpriteState {
			SpriteState(
					MotionType motion_type = STANDING,
					HorizontalFacing horizontal_facing = LEFT,
					VerticalFacing vertical_facing = HORIZONTAL) :
				motion_type(motion_type),
				horizontal_facing(horizontal_facing),
				vertical_facing(vertical_facing) {}

			MotionType motion_type;
			HorizontalFacing horizontal_facing;
			VerticalFacing vertical_facing;
		};

		friend bool operator < (const SpriteState& a, const SpriteState& b);

		bool on_ground() const { return on_ground_; }
		bool on_ground_;
		bool jump_active_;
		bool interacting_;

		void initializeSprites(Graphics& graphics);
		void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);
		SpriteState getSpriteState();

		Rectangle topCollision(units::Game delta) const;
		Rectangle bottomCollision(units::Game delta) const;
		Rectangle leftCollision(units::Game delta) const;
		Rectangle rightCollision(units::Game delta) const;

		void updateX(units::MS elapsed_time_ms, const Map& map);
		void updateY(units::MS elapsed_time_ms, const Map& map);

		units::Game x_, y_;

		units::Velocity velocity_x_, velocity_y_;
		int acceleration_x_;

		HorizontalFacing horizontal_facing_;
		VerticalFacing vertical_facing_;

		//boost::scoped_ptr<Sprite> sprite_;
		std::map<SpriteState, boost::shared_ptr<Sprite>> sprites_;

	public:
		Player(Graphics& graphics, units::Game x, units::Game y);

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
};

#endif // PLAYER_H_
