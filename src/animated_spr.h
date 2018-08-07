#ifndef ANIMATION_SPR_H_
#define ANIMATION_SPR_H_

#include "sprite.h"
#include "game.h"
#include "units.h"

class Animated_spr : public Sprite {
	private:
		const units::MS frame_time_;
		const units::Frame frames_num_;
		units::Frame current_frame_;
		units::MS elapsed_time_; // Elapsed time since last frame change.

		void update(units::MS elapsed_time_ms);
	public:
		Animated_spr(
				Graphics& graphics,
				const std::string& file_path,
				units::Pixel source_x, units::Pixel source_y,
				units::Pixel width, units::Pixel height,
				units::FPS fps, units::Frame frames_num);
		~Animated_spr();
};

#endif // ANIMATION_H_
