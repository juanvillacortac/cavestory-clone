#ifndef CAMERA_H_
#define CAMERA_H_

#include "kinematics.h"
#include "units.h"

#include <SDL2/SDL.h>

struct Map;

class Camera {
	private:
		SDL_Rect camera;

		units::Tile width_, height_;

		Kinematics kinematics_x, kinematics_y;
	public:
		Camera() :
			kinematics_x(0.0f, 0.0f), kinematics_y(0.0f, 0.0f){}

		void init(
				units::Game x, units::Game y,
				units::Tile width, units::Tile height);

		void update(
				units::Game x, units::Game y,
				units::Tile map_rows, units::Tile map_cols);

		void lookUp(units::Tile tiles, float velocity);
		void lookDown(units::Tile tiles, float velocity);
		void lookLeft(units::Tile tiles, float velocity);
		void lookRight(units::Tile tiles, float velocity);

		SDL_Rect& get() { return camera; }
};

#endif // CAMERA_H_
