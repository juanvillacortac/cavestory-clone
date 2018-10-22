#ifndef TTF_TEXTS_H_
#define TTF_TEXTS_H_

#include "units.h"

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

struct Graphics;

class TTFText {
	private:
		TTF_Font* font_;
		SDL_Surface* text_surface_;

		units::Game x_;
		units::Game y_;
	public:
		TTFText(
				Graphics& graphics,
				const char* string,
				units::Pixel size,
				units::Game x, units::Game y,
				Uint8 fR, Uint8 fG, Uint8 fB,
				Uint8 bR, Uint8 bG, Uint8 bB,
				bool alpha);
		~TTFText() {
			TTF_CloseFont(font_);
		}

		void draw(Graphics& graphics);
};

#endif // TTF_TEXTS_H_
