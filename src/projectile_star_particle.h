#ifndef PROJECTILE_STAR_PARTICLE_H_
#define PROJECTILE_STAR_PARTICLE_H_

#include "immobile_single_loop_particle.h"

class ProjectileStarParticle : public ImmobileSingleLoopParticle {
	public:
		ProjectileStarParticle(Graphics& graphics, units::Game x, units::Game y);
};

#endif // PROJECTILE_STAR_PARTICLE_H_ 
