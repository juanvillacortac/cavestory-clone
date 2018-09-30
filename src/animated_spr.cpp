#include "animated_spr.h"

Animated_spr::Animated_spr(
		Graphics& graphics,
		const std::string& file_name,
		units::Pixel source_x, units::Pixel source_y,
		units::Pixel width, units::Pixel height,
		units::FPS fps, units::Frame frames_num) : 
	Sprite(graphics, file_name, source_x, source_y, width, height),
	frame_timer_(1000 / fps),
	frames_num_(frames_num),
	current_frame_(0),
	num_completed_loops_(0)
{
}

Animated_spr::~Animated_spr() {
}

void Animated_spr::update() {
	if (frame_timer_.expired()) {
		++current_frame_;
		frame_timer_.reset();
		if (current_frame_ < frames_num_) {
			source_rect_.x += source_rect_.w;
		} else {
			source_rect_.x -= source_rect_.w * (frames_num_ - 1);
			current_frame_ = 0;
			num_completed_loops_++;
		}
	}
}
