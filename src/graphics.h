#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>
#include <map>

struct SDL_Surface;
struct SDL_Rect;

class Graphics {
	private:
		typedef std::map<std::string, SDL_Surface*> SpriteMap;

		bool fullscreen_;

		SpriteMap spr_sheets_;

		SDL_Surface* screen_;
	public:
		typedef SDL_Surface* SurfaceID;
		Graphics();
		~Graphics();

		SurfaceID loadImage(const std::string& file_name, bool black_to_alpha = false);

		void blitSurface(
				SurfaceID source,
				SDL_Rect* source_rectangle,
				SDL_Rect* destination_rectangle);

		void clear();
		void flip();

		void setVideo();
};

#endif // GRAPHICS_H_
