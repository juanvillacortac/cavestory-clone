#ifndef GRAPHICS_H_
#define GRAPHICS_H_

struct SDL_Surface;
struct SDL_Rect;

class Graphics {
	private:
		SDL_Surface* screen_;
	public:
		Graphics();
		~Graphics();

		void blitSurface(
				SDL_Surface* source,
				SDL_Rect* source_rectangle,
				SDL_Rect* destination_rectangle);

		void clear();
		void flip();
};

#endif // GRAPHICS_H_
