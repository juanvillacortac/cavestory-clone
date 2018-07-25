#ifndef ANIMATION_SPR_H_
#define ANIMATION_SPR_H_

#include "sprite.h"
#include "game.h"

class Animated_spr : public Sprite {
	private:
		const int frame_time_;
		const int frames_num_;
		int current_frame_;
		int elapsed_time_; // Elapsed time since last frame change.

		void update(int elapsed_time_ms);
	public:
		Animated_spr(
				const std::string& file_path,
				int source_x, int source_y,
				int width, int height,
				int fps, int frames_num);
		~Animated_spr();
};

#endif // ANIMATION_H_
