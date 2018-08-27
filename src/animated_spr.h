#ifndef ANIMATION_SPR_H_
#define ANIMATION_SPR_H_

#include "sprite.h"
#include "game.h"
#include "units.h"
#include "timer.h"

class Animated_spr : public Sprite {
	private:
		Timer frame_timer_;
		const units::Frame frames_num_;
		units::Frame current_frame_;

		int num_completed_loops_;
	public:
		Animated_spr(
				Graphics& graphics,
				const std::string& file_name,
				units::Pixel source_x, units::Pixel source_y,
				units::Pixel width, units::Pixel height,
				units::FPS fps, units::Frame frames_num);

		void update();

		int num_completed_loops() const
		{ return num_completed_loops_; }

		~Animated_spr();
};

#endif // ANIMATION_H_
