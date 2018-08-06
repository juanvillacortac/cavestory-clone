#ifndef GAME_H_
#define GAME_H_

#include "units.h"

#include <boost/scoped_ptr.hpp>

struct Graphics;
struct Player;
struct Map;

class Game {
	private:
		void eventLoop();
		void update(units::MS elapsed_time_ms);
		void draw(Graphics& graphics);

		boost::scoped_ptr<Player> player_;
		boost::scoped_ptr<Map> map_;
	public:
		Game();
		~Game();

		static int kTileSize;
		static int kScreenWidth;
		static int kScreenHeight;

		template <typename T>
		static T gameUnitsToPixels(T gameUnits);
};

template <typename T>
T Game::gameUnitsToPixels(T gameUnits) {
	return gameUnits * Game::kTileSize / 32;
}

#endif // GAME_H_
