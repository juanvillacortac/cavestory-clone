#ifndef SIMPLE_COLLISION_RECTANGLE_H_
#define SIMPLE_COLLISION_RECTANGLE_H_

#include "collision_rectangle.h"

#include <assert.h>

class SimpleCollisionRectangle : public CollisionRectangle {
	private:
		Rectangle rectangle_;
	public:
		SimpleCollisionRectangle(const Rectangle& rectangle) :
			rectangle_(rectangle) {}

		Rectangle boundingBox() const;

		Rectangle topCollision(units::Game x, units::Game y, units::Game delta) const {
			assert(delta <= 0);

			return Rectangle(
					x + rectangle_.left(),
					y + rectangle_.top() + delta,
					rectangle_.width(),
					rectangle_.height() - delta
					);
		}

		Rectangle bottomCollision(units::Game x, units::Game y, units::Game delta) const {
			assert(delta >= 0);

			return Rectangle(
					x + rectangle_.left(),
					y + rectangle_.top(),
					rectangle_.width(),
					rectangle_.height() + delta
					);
		}

		Rectangle leftCollision(units::Game x, units::Game y, units::Game delta) const {
			assert(delta <= 0);

			return Rectangle(
					x + rectangle_.left() + delta,
					y + rectangle_.top(),
					rectangle_.width() - delta,
					rectangle_.height() + delta
					);
		}

		Rectangle rightCollision(units::Game x, units::Game y, units::Game delta) const {
			assert(delta >= 0);

			return Rectangle(
					x + rectangle_.left(),
					y + rectangle_.top(),
					rectangle_.width() + delta,
					rectangle_.height()
					);
		}
};

#endif // SIMPLE_COLLISION_RECTANGLE_H_
