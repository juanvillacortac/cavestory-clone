#include "bat.h"
#include "animated_spr.h"
#include "graphics.h"

namespace {
	const units::Frame kNumFlyFrames = 3;
	const units::FPS kFlyFps = 30;

	const units::AngularVelocity kAngularVelocity = 120.0f / 1000.0f;

	const units::Game kFlightAmplitude = 5 * units::kHalfTile;

	const units::HP kContactDamage = 1;
}

Bat::Bat(Graphics& graphics, units::Game x, units::Game y) :
	center_y_(y),
	x_(x), y_(y),
	flight_angle_(0.0f) {
	initializeSprites(graphics);
}

void Bat::initializeSprites(Graphics& graphics) {
	for(int facing = FIRST_FACING; facing < LAST_FACING; facing++) {
		initializeSprite(graphics, SpriteState(Facing(facing)));
	}
}

void Bat::initializeSprite(Graphics& graphics, const SpriteState& sprite_state) {
	units::Tile tile_y = sprite_state.facing == RIGHT ? 3 : 2;

	sprites_[sprite_state] = boost::shared_ptr<Sprite>(new Animated_spr(
				graphics, "assets/NpcCemet.bmp",
				units::tileToPixel(2), units::tileToPixel(tile_y),
				units::tileToPixel(1), units::tileToPixel(1),
				kFlyFps, kNumFlyFrames
				)
			);
}

Bat::SpriteState Bat::getSpriteState() const {
	return SpriteState(facing_);
}

units::HP Bat::contactDamage() const {
   return kContactDamage;
}

void Bat::update(units::MS elapsed_time_ms, units::Game player_x) {
	flight_angle_ += kAngularVelocity * elapsed_time_ms;

	facing_ = x_ + units::kHalfTile > player_x ?
		LEFT : RIGHT;

	y_ = center_y_ +
		kFlightAmplitude *
		units::Game(std::sin(units::degreesToRadians(flight_angle_)));

	sprites_[getSpriteState()]->update(elapsed_time_ms);
}

void Bat::draw(Graphics& graphics) const {
	sprites_.at(getSpriteState())->draw(graphics, x_, y_);
}
