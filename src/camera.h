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

		units::MS delta_time;
	public:
		Camera() :
			kinematics_x(0.0f, 0.0f), kinematics_y(0.0f, 0.0f) {}

		void init(
				units::Game x, units::Game y,
				units::Tile width, units::Tile height);

		void update(
				units::MS elapsed_time,
				units::Game x, units::Game y,
				units::Tile map_rows, units::Tile map_cols);
		void updateX(units::MS elapsed_time);
		void updateY(units::MS elapsed_time);

		void lookUp(units::Tile tiles);
		void lookDown(units::Tile tiles);
		void lookLeft(units::Tile tiles);
		void lookRight(units::Tile tiles);

		SDL_Rect& get() { return camera; }
};

#endif // CAMERA_H_
