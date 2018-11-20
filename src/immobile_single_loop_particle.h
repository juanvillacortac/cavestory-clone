#ifndef IMMOBILE_SINGLE_LOOP_PARTICLE_H_
#define IMMOBILE_SINGLE_LOOP_PARTICLE_H_

#include "particle.h"
#include "animated_spr.h"

class ImmobileSingleLoopParticle : public Particle {
	private:
		const units::Game x_, y_;
		Animated_spr sprite_;
	public:
		ImmobileSingleLoopParticle(Graphics& graphics,
				const std::string& sprite_name, 
				units::Pixel source_x, units::Pixel source_y,
				units::Pixel source_width, units::Pixel source_height,
				units::FPS fps, units::Frame num_frames,
				units::Game x, units::Game y);

		bool update(units::MS elapsed_time);
		void draw(Graphics& graphics, SDL_Rect& camera);
		virtual ~ImmobileSingleLoopParticle() {}
};

#endif // IMMOBILE_SINGLE_LOOP_PARTICLE_H_
