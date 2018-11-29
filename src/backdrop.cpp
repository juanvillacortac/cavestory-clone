#include "backdrop.h"
#include "game.h"

#include <SDL2/SDL.h>

namespace {
	const units::Tile kBackgroundSize = 4;
}

FixedBackdrop::FixedBackdrop(
		const std::string& path,
		Graphics& graphics,
		units::Tile rows, units::Tile cols) :
	rows_(rows),
	cols_(cols)
{
	surface_id_ = graphics.loadImage(path);
}

void FixedBackdrop::draw(Graphics& graphics, SDL_Rect& camera) const {
	for (units::Tile x = 0; x < cols_; x += kBackgroundSize) {
		for (units::Tile y = 0; y < rows_; y += kBackgroundSize) {
			SDL_Rect destination_rectangle;

			destination_rectangle.x = units::tileToPixel(x);
			destination_rectangle.y = units::tileToPixel(y);

			graphics.render(surface_id_, NULL, &destination_rectangle);
		}
	}
}

DinamicBackdrop::DinamicBackdrop(
		const std::string& path,
		Graphics& graphics,
		units::Tile rows, units::Tile cols,
		float profundity) :
	rows_(rows),
	cols_(cols),
	profundity_(profundity)
{
	surface_id_ = graphics.loadImage(path);
}

void DinamicBackdrop::draw(Graphics& graphics, SDL_Rect& camera) const {
	for (units::Tile x = 0; x < cols_; x += kBackgroundSize) {
		for (units::Tile y = 0; y < rows_; y += kBackgroundSize) {
			SDL_Rect destination_rectangle;

			destination_rectangle.x = units::tileToPixel(x) - (camera.x / profundity_);
			destination_rectangle.y = units::tileToPixel(y) - (camera.y / profundity_);

			graphics.render(surface_id_, NULL, &destination_rectangle);
		}
	}
}
