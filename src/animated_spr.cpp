#include "animated_spr.h"

Animated_spr::Animated_spr(
		Graphics& graphics,
		const std::string& file_path,
		int source_x, int source_y,
		int width, int height,
		units::FPS fps, int frames_num) : 
	Sprite(graphics, file_path, source_x, source_y, width, height),
	frame_time_(1000 / fps),
	frames_num_(frames_num),
	current_frame_(0),
	elapsed_time_(0)
{
}

Animated_spr::~Animated_spr() {
}

void Animated_spr::update(units::MS elapsed_time_ms) {
	elapsed_time_ += elapsed_time_ms;

	if(elapsed_time_ > frame_time_) {
		++current_frame_;
		elapsed_time_ = 0;
		if(current_frame_ < frames_num_) {
			source_rect_.x += Game::kTileSize;
		} else {
			source_rect_.x -= Game::kTileSize * (frames_num_ - 1);
			current_frame_ = 0;
		}
	}
}
