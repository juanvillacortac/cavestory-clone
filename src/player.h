#ifndef PLAYER_H_
#define PLAYER_H_

#include "sprite.h"

//#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <map>

struct Sprite;
struct Graphics;

class Player {
	private:
		enum MotionType {
			STANDING,
			WALKING
		};
		enum HorizontalFacing {
			LEFT,
			RIGHT
		};

		struct SpriteState {
			SpriteState(
					MotionType motion_type = STANDING,
					HorizontalFacing horizontal_facing = LEFT) :
				motion_type(motion_type),
				horizontal_facing(horizontal_facing) {}

			MotionType motion_type;
			HorizontalFacing horizontal_facing;
		};

		friend bool operator < (const SpriteState& a, const SpriteState& b);

		struct Jump {
			private:
				int time_remaining_ms_;
				bool active_;
			public:
				Jump() : time_remaining_ms_(0), active_(false) {}

				void update(int elapsed_time_ms);
				void reset();

				void reactivate() { active_ = time_remaining_ms_ > 0; }
				void deactivate() { active_ = false; }
				bool active() const { return active_; }
		};

		Jump jump_;

		void initializeSprites(Graphics& graphics);
		SpriteState getSpriteState();

		bool on_ground() const {
			return on_ground_;
		}

		int x_, y_;

		float velocity_x_, velocity_y_;
		float acceleration_x_;

		HorizontalFacing horizontal_facing_;

		bool on_ground_;

		//boost::scoped_ptr<Sprite> sprite_;
		std::map<SpriteState, boost::shared_ptr<Sprite>> sprites_;

	public:
		Player(Graphics& graphics, int x, int y);

		void update(int elapsed_time_ms);
		void draw(Graphics& graphics);

		void startMovingLeft();
		void startMovingRight();
		void stopMoving();

		void startJump();
		void stopJump();
};

#endif // PLAYER_H_
