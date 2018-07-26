#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>
#include <map>

struct SDL_Surface;
struct SDL_Rect;

class Graphics {
	private:
		std::map<std::string, SDL_Surface*> spr_sheets_;
		SDL_Surface* screen_;
	public:
		typedef SDL_Surface* SurfaceID;
		Graphics();
		~Graphics();

		SurfaceID loadImage(const std::string& file_path);

		void blitSurface(
				SurfaceID source,
				SDL_Rect* source_rectangle,
				SDL_Rect* destination_rectangle);

		void clear();
		void flip();
};

#endif // GRAPHICS_H_
