#ifndef NUMBER_SPRITE_H_
#define NUMBER_SPRITE_H_

#include "units.h"

#include <boost/shared_ptr.hpp>
#include <vector>

struct Graphics;
struct Sprite;

class NumberSpr {
	private:
		units::Game padding_;
		std::vector<boost::shared_ptr<Sprite>> reversed_digits_;
	public:
		// if num_digits is 0, we don't care how much space it takes up.
		NumberSpr(Graphics& graphics, int number, int num_digits=0);

		void draw(Graphics& graphics, units::Game x, units::Game y);
};

#endif // NUMBER_SPRITE_H_ 
