#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "units.h"

struct Graphics;
struct SDL_Rect;

struct Particle {
	virtual bool update(units::MS elapsed_time) = 0;
	virtual void draw(Graphics& graphics, SDL_Rect& camera) = 0;
	virtual ~Particle() = 0;
};

inline Particle::~Particle() {}

#endif // PARTICLE_H_ 
