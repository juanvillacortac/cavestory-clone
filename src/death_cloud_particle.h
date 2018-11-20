#ifndef DEATH_CLOUD_PARTICLE_H_
#define DEATH_CLOUD_PARTICLE_H_

#include "animated_spr.h"
#include "particle.h"
#include "polar_vector.h"

struct ParticleTools;

class DeathCloudParticle : public Particle {
	private:
		const units::Game center_x_, center_y_;
		const units::Velocity speed_;
		PolarVector offset_;
		Animated_spr sprite_;
	public:
		DeathCloudParticle(Graphics& graphics,
				units::Game center_x, units::Game center_y,
				units::Velocity speed, units::Degrees angle);

		static void createRandomDeathClouds(
				ParticleTools& particle_tools,
				units::Game center_x, units::Game center_y,
				int num_particles);

		bool update(units::MS elapsed_time);
		void draw(Graphics& graphics, SDL_Rect& camera);
};

#endif // DEATH_CLOUD_PARTICLE_H_ 
