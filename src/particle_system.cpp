#include "particle_system.h"
#include "particle.h"

void ParticleSystem::update(units::MS elapsed_time) {
	for (ParticleSet::iterator iter = particles_.begin();
			iter != particles_.end();
	   ) {
		if ((*iter)->update(elapsed_time)) {
			iter++;
		} else {
			particles_.erase(iter++);
		}
	}
}

void ParticleSystem::draw(Graphics& graphics, SDL_Rect& camera) {
	for (ParticleSet::iterator iter = particles_.begin();
			iter != particles_.end();
			iter++) {
		(*iter)->draw(graphics, camera);
	}
}
