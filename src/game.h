#ifndef GAME_H_
#define GAME_H_

#include <boost/scoped_ptr.hpp>

struct Sprite;
struct Graphics;

class Game {
	private:
		void eventLoop();
		void update(int elapsed_time_ms);
		void draw(Graphics& graphics);

		boost::scoped_ptr<Sprite> sprite_;
	public:
		Game();
		~Game();

		static int kTileSize;
};

#endif // GAME_H_
