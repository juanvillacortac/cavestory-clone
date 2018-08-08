#ifndef GAME_H_
#define GAME_H_

#include "units.h"

#include <boost/scoped_ptr.hpp>

struct Graphics;
struct Player;
struct Bat;
struct Map;

class Game {
	private:
		void eventLoop();
		void update(units::MS elapsed_time_ms);
		void draw(Graphics& graphics);

		boost::scoped_ptr<Player> player_;
		boost::scoped_ptr<Bat> bat_;
		boost::scoped_ptr<Map> map_;
	public:
		Game();
		~Game();

		static units::Tile kScreenWidth;
		static units::Tile kScreenHeight;
};

#endif // GAME_H_
