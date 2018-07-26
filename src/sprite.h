#ifndef SPRITE_H_
#define SPRITE_H_

#include <string>
#include <SDL/SDL.h>

struct Graphics;

class Sprite {
	private:
		SDL_Surface* spr_sheet_;
	protected:
		SDL_Rect source_rect_;
	public:
		Sprite(
				Graphics& graphics,
				const std::string& file_path,
				int source_x, int source_y,
				int width, int height);
		//virtual ~Sprite();

		virtual void update(int /*elapsed_time_ms*/) {}

		void draw(Graphics& graphics, int x, int y);
};

#endif // SPRITE_H_
