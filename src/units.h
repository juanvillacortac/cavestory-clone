#ifndef UNITS_H_
#define UNITS_H_

#include "config.h"
#include "vector2d.h"

#include <cmath>

namespace units {
	typedef float Game; // Float for extra precision. Intrinsic units of position.
	typedef float Pixel; // Integer for dicrete units. Pixels values can be + or -.
	typedef unsigned int Tile; // Also discreted, but non-negative.
	typedef unsigned int Frame; // Discrete. Non-negative.

	typedef float Degrees;

	typedef unsigned int MS; // Discrete Milliseconds. Unsigned int matches SDL.
	typedef unsigned int FPS; // Frames per second (Hz or 1 / second).

	typedef float Velocity; // Game / MS.
	typedef float Acceleration; // Game / MS / MS.
	typedef float AngularVelocity; // Degrees / MS.

	typedef int HP;
	typedef int GunExperience;
	typedef unsigned int GunLevel;
	const GunLevel kMaxGunLevel = 3;

	namespace {
		const Game kTileSize = 32.0f;
		const double kPi = atan(1) * 4;

		int round(double val) {
			return (int)(val > 0.0 ? val + 0.5 : val - 0.5); 
		}
	}

	inline double degreesToRadians(Degrees degrees) {
		return degrees * kPi / 180.0f;
	}

	inline Game cos(Degrees degrees) {
		return static_cast<Game>(std::cos(degreesToRadians(degrees)));
	}

	inline Game sin(Degrees degrees) {
		return static_cast<Game>(std::sin(degreesToRadians(degrees)));
	}

	// Game to pixel
	inline Pixel gameToPixel(Game game) {
		return config::getGraphicsQuality() == config::HIGH ?
			Pixel(round(game)) :
			Pixel(round(game / 2));
	}

	// Game to tile
	inline Tile gameToTile(Game game) {
		return Tile(game / kTileSize);
	}

	// Tile to game
	inline Game tileToGame(Tile tile) {
		return tile * kTileSize;
	}

	// Tile to pixel
	inline Pixel tileToPixel(Tile tile) {
		return gameToPixel(tileToGame(tile));
	}

	const Game kHalfTile = tileToGame(1) / 2.0f;
}

typedef Vector2D<units::Tile> Tile2D;

typedef Vector2D<units::Game> Position2D;
typedef Vector2D<units::Game> Dimensions2D; 

typedef Vector2D<units::Velocity> Velocity2D; 

#endif // UNITS_H_
