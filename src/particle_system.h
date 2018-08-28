#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include "units.h"

#include <memory>
#include <set>

struct Particle;
struct Graphics;

class ParticleSystem {
	private:
		typedef std::set<std::shared_ptr<Particle>> ParticleSet;
		ParticleSet particles_;
	public:
		void addNewParticle(std::shared_ptr<Particle> particle) { particles_.insert(particle); }
		void update(units::MS elapsed_time);
		void draw(Graphics& graphics);
};

class ParticleTools {
	public:
		ParticleSystem& front_system;
		ParticleSystem& entity_system;

		Graphics& graphics;
};

#endif // PARTICLE_SYSTEM_H_ 
