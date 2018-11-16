#ifndef TTF_TEXTS_H_
#define TTF_TEXTS_H_

#include "units.h"

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct Graphics;

class TTFText {
	private:
		TTF_Font* font_;
		SDL_Surface* text_surface_;
		SDL_Texture* text_texture_;
		SDL_Renderer* renderer_;

		units::Game x_;
		units::Game y_;
	protected:
		SDL_Rect source_rect_;
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
