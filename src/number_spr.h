#ifndef NUMBER_SPRITE_H_
#define NUMBER_SPRITE_H_

#include "units.h"

#include <boost/shared_ptr.hpp>
#include <vector>

struct Graphics;
struct Sprite;

class NumberSpr {
	private:
		enum ColorType {
			RED,
			WHITE
		};

		enum OperatorType {
			PLUS,
			MINUS,
			NONE,
		};

		// if num_digits is 0, we don't care how much space it takes up.
		NumberSpr(Graphics& graphics, int number, int num_digits, ColorType color, OperatorType op);
		
		units::Game padding_;

		std::vector<boost::shared_ptr<Sprite> > reversed_glyphs_;

		units::Game width() const { return units::kHalfTile * reversed_glyphs_.size(); }
		units::Game height() const { return units::kHalfTile; }
	public:
		// Ex. " 3" in white text.
		static NumberSpr HUDNumber(Graphics& graphics, int number, int num_digits)
		{ return NumberSpr(graphics, number, num_digits, WHITE, NONE); }

		// Ex. "-30" in red text.
		static NumberSpr DamageNumber(Graphics& graphics, int number)
		{ return NumberSpr(graphics, number, 0, RED, MINUS); }

		// Ex. "+128" in white text.
		static NumberSpr ExperienceNumber(Graphics& graphics, int number)
		{ return NumberSpr(graphics, number, 0, WHITE, PLUS); }

		void draw(Graphics& graphics, units::Game x, units::Game y);

		void drawCentered(Graphics& graphics, units::Game x, units::Game y)
		{ draw(graphics, x - width() / 2, y - height() / 2); }
};

#endif // NUMBER_SPRITE_H_ 
