#ifndef CAMERA_H_
#define CAMERA_H_

#include "units.h"

#include <SDL2/SDL.h>

struct Map;

class Camera {
	private:
		SDL_Rect camera;

		units::Tile width_, height_;
	public:
		Camera(units::Tile width, units::Tile height);

		void update(units::Game x, units::Game y, units::Tile map_rows, units::Tile map_cols);

		SDL_Rect& get() { return camera; }
};

#endif // CAMERA_H_
