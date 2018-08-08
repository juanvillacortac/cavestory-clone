#include "bat.h"
#include "animated_spr.h"
#include "graphics.h"

namespace {
	const units::Frame kNumFlyFrames = 3;
	const units::FPS kFlyFps = 30;
}

Bat::Bat(Graphics& graphics, units::Game x, units::Game y) : x_(x), y_(y) {
	sprite_ = boost::shared_ptr<Sprite>(new Animated_spr(
				graphics, "assets/NpcCemet.bmp",
				units::tileToPixel(2), units::tileToPixel(2),
				units::tileToPixel(1), units::tileToPixel(1),
				kFlyFps, kNumFlyFrames
				)
			);
}

void Bat::update(units::MS elapsed_time_ms) {
	sprite_->update(elapsed_time_ms);
}

void Bat::draw(Graphics& graphics) const {
	sprite_->draw(graphics, x_, y_);
}
