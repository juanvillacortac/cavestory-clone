#include "camera.h"

Camera::Camera(units::Tile width, units::Tile height) :
	width_(width),
	height_(height)
{
	camera = {
		0,
		0,
		(int)units::tileToPixel(width),
		(int)units::tileToPixel(height)
	};
}

void Camera::update(units::Game x, units::Game y) {
	camera.x = units::gameToPixel(x - units::tileToGame(width_) / 2);
	camera.y = units::gameToPixel(y - units::tileToGame(height_) / 2);

	/*if ( camera.x < 0 ) {
		camera.x = 0;
	}
	if ( camera.y < 0 ) {
		camera.y = 0;
	}
	if ( camera.x > units::tileToPixel(width_) - camera.w ) {
		camera.x = units::tileToPixel(width_) - camera.w;
	}
	if( camera.y > units::tileToPixel(height_) - camera.h ) {
		camera.y = units::tileToPixel(height_) - camera.h;
	}*/
}