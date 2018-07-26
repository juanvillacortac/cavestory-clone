#ifndef PLAYER_H_
#define PLAYER_H_

#include "sprite.h"

#include <boost/scoped_ptr.hpp>

struct Sprite;
struct Graphics;

class Player {
	private:
		int x_, y_;

		boost::scoped_ptr<Sprite> sprite_;

		float velocity_x_;
		float velocity_y_;
		float acceleration_x_;
	public:
		Player(Graphics& graphics, int x, int y);

		void update(int elapsed_time_ms);
		void draw(Graphics& graphics);

		void startMovingLeft();
		void startMovingRight();
		void stopMoving();
};

#endif // PLAYER_H_
