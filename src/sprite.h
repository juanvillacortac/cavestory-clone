#ifndef SPRITE_H_
#define SPRITE_H_

#include "units.h"

#include <string>
#include <SDL/SDL.h>

struct Graphics;

class Sprite {
	private:
		SDL_Surface* spr_sheet_;
	protected:
		SDL_Rect source_rect_;
	public:
		Sprite(
				Graphics& graphics,
				const std::string& file_path,
				units::Pixel source_x, units::Pixel source_y,
				units::Pixel width, units::Pixel height);

		virtual void update(units::MS) {}

		void draw(Graphics& graphics, units::Game x, units::Game y);
};

#endif // SPRITE_H_
