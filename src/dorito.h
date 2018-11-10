#ifndef DORITO_H_
#define DORITO_H_

#include "pickup.h"
#include "kinematics.h"
#include "animated_spr.h"
#include "map_collidable.h"

class Dorito :
	public Pickup,
	private MapCollidable
{
	public:
		enum SizeType {
			SMALL = 0,
			MEDIUM = 1,
			LARGE = 2
		};

		Dorito(Graphics& graphics, units::Game center_x, units::Game center_y, SizeType size);

		Rectangle collisionRectangle() const;
		bool update(units::MS elapsed_time, const Map& map);
		void draw(Graphics& graphics);
		int value() const;
		PickupType type() const { return EXPERIENCE; }
	private:
		void onCollision(sides::SideType side, bool is_delta_direction);
		void onDelta(sides::SideType side) {}

		Kinematics kinematics_x_, kinematics_y_;

		Animated_spr sprite_;

		SizeType size_;

		Timer timer_;
};

#endif // DORITO_H_
