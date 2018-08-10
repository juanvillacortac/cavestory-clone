#include "graphics.h"
#include "game.h"

#include <SDL/SDL.h>

namespace {
	const int kBitsPerPixel = 32;
}

Graphics::Graphics() {
	fullscreen_ = false;
	setVideo();
	/*screen_ = SDL_SetVideoMode(
			units::tileToPixel(Game::kScreenWidth),
			units::tileToPixel(Game::kScreenHeight),
			kBitsPerPixel,
			0);*/

	SDL_ShowCursor(SDL_DISABLE);
}

Graphics::~Graphics() {
	for(SpriteMap::iterator iter = spr_sheets_.begin();
			iter != spr_sheets_.end();
			iter++) {
		SDL_FreeSurface(iter->second);
	}
	SDL_FreeSurface(screen_);
}

Graphics::SurfaceID Graphics::loadImage(const std::string& file_path, bool black_to_alpha) {
	// If we haven't loaded in the spritesheet
	if(spr_sheets_.count(file_path) == 0) {
		// Load it
		spr_sheets_[file_path] = SDL_LoadBMP(file_path.c_str());
		if(black_to_alpha) {
			const Uint32 black_color = SDL_MapRGB(spr_sheets_[file_path]->format, 0, 0, 0);
			SDL_SetColorKey(spr_sheets_[file_path], SDL_SRCCOLORKEY, black_color);
		}
		// Error handler
		if(spr_sheets_[file_path] == NULL) {
			// Could not load the image for whatever reason, print to stderr.
			fprintf(stderr, "Could not find image: %s\n", file_path.c_str());
			// Don't try to continue if we couldn't load an image, just exit.
			exit(EXIT_FAILURE);
		}
	}
	return spr_sheets_[file_path];
}

void Graphics::blitSurface(
		SurfaceID source,
		SDL_Rect* source_rectangle,
		SDL_Rect* destination_rectangle) {
	SDL_BlitSurface(source, source_rectangle, screen_, destination_rectangle);
}

void Graphics::clear() {
	SDL_FillRect(screen_, NULL /*destination_rectangle*/, 0 /*color*/);
}

void Graphics::flip() {
	SDL_Flip(screen_);
}

void Graphics::setVideo() {
	switch(fullscreen_) {
		case true:
			screen_ = SDL_SetVideoMode(
					units::tileToPixel(Game::kScreenWidth),
					units::tileToPixel(Game::kScreenHeight),
					kBitsPerPixel,
					SDL_FULLSCREEN);
			fullscreen_ = false;
			break;
		case false:
			screen_ = SDL_SetVideoMode(
					units::tileToPixel(Game::kScreenWidth),
					units::tileToPixel(Game::kScreenHeight),
					kBitsPerPixel,
					0);
			fullscreen_ = true;
			break;
	}
}
