#ifndef COLLISION_RECTANGLE_H_
#define COLLISION_RECTANGLE_H_

#include "rectangle.h"

class CollisionRectangle {
	public:
		virtual ~CollisionRectangle() = 0;

		virtual Rectangle boundingBox() const = 0;

		virtual Rectangle topCollision(units::Game x, units::Game y, units::Game delta) const = 0;

		virtual Rectangle bottomCollision(units::Game x, units::Game y, units::Game delta) const = 0;

		virtual Rectangle leftCollision(units::Game x, units::Game y, units::Game delta) const = 0;

		virtual Rectangle rightCollision(units::Game x, units::Game y, units::Game delta) const = 0;
};

inline CollisionRectangle::~CollisionRectangle() {}

#endif // COLLISION_RECTANGLE_H_
