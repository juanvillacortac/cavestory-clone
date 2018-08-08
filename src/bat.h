#ifndef BAT_H_
#define BAT_H_

#include "units.h"

#include <boost/shared_ptr.hpp>

struct Graphics;
struct Sprite;

class Bat {
	private:
		units::Game x_, y_;

		boost::shared_ptr<Sprite> sprite_;
	public:
		Bat(Graphics& graphics, units::Game x, units::Game y);

		void update(units::MS elapsed_time_ms);
		void draw(Graphics& graphics) const;
};

#endif // BAT_H_
