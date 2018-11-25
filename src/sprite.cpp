#include "sprite.h"
#include "graphics.h"

Sprite::Sprite(
		Graphics& graphics,
		const std::string& file_name,
		units::Pixel source_x, units::Pixel source_y,
		units::Pixel width, units::Pixel height) {
	const bool black_to_alpha = true;

	spr_sheet_ = graphics.loadImage(file_name, black_to_alpha);
	source_rect_.x = source_x;
	source_rect_.y = source_y;
	source_rect_.w = width;
	source_rect_.h = height;
}

void Sprite::draw(Graphics& graphics, units::Game x, units::Game y, SDL_Rect* camera) {
	SDL_Rect destination_rectangle;
	if (!camera) {
		destination_rectangle.x = units::gameToPixel(x);
		destination_rectangle.y = units::gameToPixel(y);
	} else {
		destination_rectangle.x = units::gameToPixel(x) - camera->x;
		destination_rectangle.y = units::gameToPixel(y) - camera->y;
	}
	graphics.render(spr_sheet_, &source_rect_, &destination_rectangle);
}
