#ifndef DAMAGE_TEXT_H_
#define DAMAGE_TEXT_H_

#include "units.h"
#include "timer.h"

struct Graphics;

class DamageText {
	private:
		units::Game center_x_, center_y_;
		units::Game offset_y_;

		units::HP damage_;

		Timer timer_;

		bool should_rise_;
	public:
		DamageText();

		void setDamage(units::HP damage);
		void setPosition(units::Game center_x, units::Game center_y);
		void update(units::MS elapsed_time);
		void draw(Graphics& graphics);
};

#endif // DAMAGE_TEXT_H_
