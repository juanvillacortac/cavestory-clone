#include "ttf_texts.h"
#include "graphics.h"

TTFText::TTFText(
		Graphics& graphics,
		const char* string,
		units::Pixel size,
		units::Game x, units::Game y,
		Uint8 fR, Uint8 fG, Uint8 fB,
		Uint8 bR, Uint8 bG, Uint8 bB,
		bool alpha) :
	x_(x), y_(y)
{
	TTF_Init();

	font_ = TTF_OpenFont("assets/font.ttf", units::gameToPixel(size));

	SDL_Color foregroundColor = { fR, fG, fB };
	SDL_Color backgroundColor = { bR, bG, bB };

	text_surface_ = TTF_RenderText_Shaded(font_, string, foregroundColor, backgroundColor);

	if (alpha) {
		const Uint32 black_color = SDL_MapRGB(text_surface_->format, 0, 0, 0);
		SDL_SetColorKey(text_surface_, SDL_SRCCOLORKEY, black_color);
	}
}

void TTFText::draw(Graphics& graphics) {
	SDL_Rect destination_rectangle;
	destination_rectangle.x = units::gameToPixel(x_);
	destination_rectangle.y = units::gameToPixel(y_);
	graphics.blitNullSurface(text_surface_, &destination_rectangle);
}
