#ifndef SPRITE_H_
#define SPRITE_H_

#include "units.h"

#include <string>
#include <SDL2/SDL.h>

struct Graphics;

class Sprite {
	private:
		SDL_Texture* spr_sheet_;
	protected:
		SDL_Rect source_rect_;
	public:
		Sprite(
				Graphics& graphics,
				const std::string& file_name,
				units::Pixel source_x, units::Pixel source_y,
				units::Pixel width, units::Pixel height);

		virtual void update() {}

		void draw(Graphics& graphics, units::Game x, units::Game y, SDL_Rect* camera);
};

#endif // SPRITE_H_
