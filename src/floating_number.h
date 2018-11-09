#ifndef FLOATING_NUMBER_H_
#define FLOATING_NUMBER_H_

#include "units.h"
#include "timer.h"

struct Graphics;

class FloatingNumber {
	public:
		enum NumberType {
			DAMAGE,
			EXPERIENCE
		};

		FloatingNumber(NumberType type);

		void addValue(int value);
		void setPosition(units::Game center_x, units::Game center_y);
		bool update(units::MS elapsed_time);
		void draw(Graphics& graphics);
	private:
		units::Game center_x_, center_y_;
		units::Game offset_y_;

		int value_;

		Timer timer_;

		bool should_rise_;

		const NumberType type_;
};

#endif // FLOATING_NUMBER_H_
