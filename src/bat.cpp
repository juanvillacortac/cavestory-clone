#include "bat.h"
#include "animated_spr.h"
#include "graphics.h"

namespace {
	const units::Frame kNumFlyFrames = 3;
	const units::FPS kFlyFps = 13;

	const units::AngularVelocity kAngularVelocity = 120.0f / 1000.0f;
}

Bat::Bat(Graphics& graphics, units::Game x, units::Game y) :
	x_(x), y_(y),
	flight_angle_(0.0f) {
	sprite_ = boost::shared_ptr<Sprite>(new Animated_spr(
				graphics, "assets/NpcCemet.bmp",
				units::tileToPixel(2), units::tileToPixel(2),
				units::tileToPixel(1), units::tileToPixel(1),
				kFlyFps, kNumFlyFrames
				)
			);
}

void Bat::update(units::MS elapsed_time_ms) {
	flight_angle_ += kAngularVelocity * elapsed_time_ms;

	sprite_->update(elapsed_time_ms);
}

void Bat::draw(Graphics& graphics) const {
	const units::Game y = y_ + units::tileToGame(5) / 2.0f *
		std::sin(units::degreesToRadians(flight_angle_));

	sprite_->draw(graphics, x_, y);
}
