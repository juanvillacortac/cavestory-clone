#include "backdrop.h"
#include "game.h"

#include <SDL2/SDL.h>

namespace {
	const units::Tile kBackgroundSize = 4;
}

FixedBackdrop::FixedBackdrop(const std::string& path, Graphics& graphics) {
	surface_id_ = graphics.loadImage(path);
}

void FixedBackdrop::draw(Graphics& graphics, SDL_Rect& camera) const {
	for (units::Tile x = 0; x < 20*2; x += kBackgroundSize) {
		for (units::Tile y = 0; y < 15 *2; y += kBackgroundSize) {
			SDL_Rect destination_rectangle;

			destination_rectangle.x = units::tileToPixel(x) - (camera.x / 4);
			destination_rectangle.y = units::tileToPixel(y) - (camera.y / 4);

			graphics.blitSurface(surface_id_, NULL, &destination_rectangle);
		}
	}
}
