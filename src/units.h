#ifndef UNITS_H_
#define UNITS_H_

#include <cmath>

namespace units {
	typedef float Game; // Float for extra precision. Intrinsic units of position.
	typedef float Pixel; // Integer for dicrete units. Pixels values can be + or -.
	typedef unsigned int Tile; // Also discreted, but non-negative.
	typedef unsigned int Frame; // Discrete. Non-negative.

	typedef unsigned int MS; // Discrete Milliseconds. Unsigned int matches SDL.
	typedef unsigned int FPS; // Frames per second (Hz or 1 / second).

	typedef float Velocity; // Game / MS.
	typedef float Acceleration; // Game / MS / MS.

	namespace {
		const Game kTileSize = 32.0f;
	}

	// Game to pixel
	inline Pixel gameToPixel(Game game) {
		// TODO: quit assuming 16x16
		return Pixel(round(game)); // game / 2 for 16x16
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
}

#endif // UNITS_H_
