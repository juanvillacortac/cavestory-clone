#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>
#include <map>

struct SDL_Rect;
struct SDL_Texture;
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

class Graphics {
	private:
		typedef std::map<std::string, SDL_Texture*> SpriteMap;

		SpriteMap spr_sheets_;

		SDL_Window* window_;
		SDL_Renderer* renderer_;

		bool windowed = true;
	public:
		typedef SDL_Texture* SurfaceID;
		Graphics();
		~Graphics();

		SDL_Texture* surfaceToTexture(SDL_Surface* surface);
		SurfaceID loadImage(const std::string& file_name, bool black_to_alpha = false);

		void render(
				SurfaceID source,
				SDL_Rect* source_rectangle,
				SDL_Rect* destination_rectangle);

		void clear();
		void flip();

		void setFullscreen();
};

#endif // GRAPHICS_H_
