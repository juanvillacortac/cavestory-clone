#include "projectile_star_particle.h"

const std::string kSpriteName("Caret");

const units::Tile kSourceX = 0;
const units::Tile kSourceY = 3;

const units::Tile kSourceWidth = 1;
const units::Tile kSourceHeight = 1;

const units::FPS kFps = 18;

const units::Frame kNumFrames = 4;

ProjectileStarParticle::ProjectileStarParticle(Graphics& graphics, units::Game x, units::Game y) :
	ImmobileSingleLoopParticle(graphics, kSpriteName, 
			units::tileToPixel(kSourceX), units::tileToPixel(kSourceY), 
			units::tileToPixel(kSourceWidth), units::tileToPixel(kSourceHeight), 
			kFps, kNumFrames,
			x, y)
{}
