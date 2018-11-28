#include "graphics.h"
#include "game.h"

#include <SDL2/SDL.h>

namespace {
	const units::Pixel kScreenWidth = units::tileToPixel(Game::kScreenWidth);
	const units::Pixel kScreenHeight = units::tileToPixel(Game::kScreenHeight);
}

Graphics::Graphics() {
	window_ = SDL_CreateWindow("Cave Story Clone - SDL2",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			kScreenWidth,
			kScreenHeight,
			0);

	renderer_ = SDL_CreateRenderer(
			window_, -1,
			SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC |
			SDL_RENDERER_TARGETTEXTURE
			);

	backbuffer_ = SDL_CreateTexture(
			renderer_,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			kScreenWidth, kScreenHeight
			);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

	SDL_RenderSetLogicalSize(renderer_, kScreenWidth, kScreenHeight);

	if (config::getScaleType() == config::INT)
		SDL_RenderSetIntegerScale(renderer_, SDL_TRUE);

	windowed = config::getFullscreen();
	setFullscreen();

	SDL_ShowCursor(SDL_DISABLE);
}

Graphics::~Graphics() {
	for (SpriteMap::iterator iter = spr_sheets_.begin();
			iter != spr_sheets_.end();
			iter++) {
		SDL_DestroyTexture(iter->second);
	}

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

SDL_Texture* Graphics::surfaceToTexture(SDL_Surface* surface) {
	return SDL_CreateTextureFromSurface(renderer_, surface);
}

Graphics::SurfaceID Graphics::loadImage(const std::string& file_name, bool black_to_alpha) {
	const std::string file_path = config::getGraphicsQuality() == config::ORIGINAL ?
		"assets/" + file_name + ".pbm" :
		"assets/" + file_name + ".bmp";

	// if we have not loaded in the spritesheet
	if (spr_sheets_.count(file_path) == 0) {
		// load it in now
		SDL_Surface* image = SDL_LoadBMP(file_path.c_str());

		if (!image) {
			fprintf(stderr, "Could not find image: %s\n", file_path.c_str());
			exit(EXIT_FAILURE);
		}

		if (black_to_alpha) {
			const Uint32 black_color = SDL_MapRGB(image->format, 0, 0, 0);
			SDL_SetColorKey(image, SDL_TRUE, black_color);
		}

		spr_sheets_[file_path] = surfaceToTexture(image);//SDL_CreateTextureFromSurface(renderer_, image);
		SDL_FreeSurface(image);
	}

	return spr_sheets_[file_path];
}

void Graphics::render(
		SurfaceID source,
		SDL_Rect* source_rectangle,
		SDL_Rect* destination_rectangle) {
	if (source_rectangle) {
		destination_rectangle->w = source_rectangle->w;
		destination_rectangle->h = source_rectangle->h;
	} else {
		uint32_t format;
		int access, w, h;
		SDL_QueryTexture(source, &format, &access, &w, &h);
		destination_rectangle->w = w;
		destination_rectangle->h = h;
	}

	SDL_SetRenderTarget(renderer_, backbuffer_);

	SDL_RenderCopy(renderer_, source, source_rectangle, destination_rectangle);
}

void Graphics::clear() {
	SDL_RenderClear(renderer_); 
}

void Graphics::flip() {
	SDL_SetRenderTarget(renderer_, NULL);
	SDL_RenderCopy(renderer_, backbuffer_, NULL, NULL);
	SDL_RenderPresent(renderer_); 
}

void Graphics::setFullscreen() {
	windowed = !windowed;

	if (windowed) {
		SDL_SetWindowFullscreen(window_, 0);
	} else {
		SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
}
