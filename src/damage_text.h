#ifndef DAMAGE_TEXT_H_
#define DAMAGE_TEXT_H_

#include "units.h"
#include "timer.h"

struct Graphics;

class DamageText {
	private:
		units::HP damage_;
		units::Game offset_y_;
		Timer timer_;
	public:
		DamageText();

		void setDamage(units::HP damage);
		void update(units::MS elapsed_time);
		void draw(Graphics& graphics, units::Game center_x, units::Game center_y);
};

#endif // DAMAGE_TEXT_H_
