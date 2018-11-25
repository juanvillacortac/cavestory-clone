#include "camera.h"
#include "accelerators.h"
#include "map.h"

#include <iostream>

namespace {
	const units::Acceleration kAcceleration = 0.00083007812f;
	const units::Velocity kVelocity = 0.05f;

	const ConstantAccelerator kAccelerator(kAcceleration, kVelocity);
}

void Camera::init(units::Game x, units::Game y, units::Tile width, units::Tile height) {
	width_ = width;
	height_ = height;

	kinematics_x.position = units::gameToPixel((x) - units::tileToGame(width_) / 2);
	kinematics_y.position = units::gameToPixel((y) - units::tileToGame(height_) / 2);

	camera = {
		(int)kinematics_x.position,
		(int)kinematics_y.position,
		(int)units::tileToPixel(width_),
		(int)units::tileToPixel(height_)
	};
}

void Camera::update(
		units::MS elapsed_time,
		units::Game x, units::Game y,
		units::Tile map_rows, units::Tile map_cols) {

	kinematics_x.position = units::gameToPixel(x - units::tileToGame(width_) / 2);
	kinematics_y.position = units::gameToPixel(y - units::tileToGame(height_) / 2);

	updateX(elapsed_time);
	updateY(elapsed_time);

	if ( camera.x < 0 ) {
		camera.x = 0;
	}
	if ( camera.y < 0 ) {
		camera.y = 0;
	}
	if ( camera.x > units::tileToPixel(map_cols) - camera.w ) {
		camera.x = units::tileToPixel(map_cols) - camera.w;
	}
	if( camera.y > units::tileToPixel(map_rows) - camera.h ) {
		camera.y = units::tileToPixel(map_rows) - camera.h;
	}
}

void Camera::updateX(units::MS elapsed_time) {
	const Accelerator* accelerator;

	accelerator = &kAccelerator;

	accelerator->updateVelocity(kinematics_x, elapsed_time);

	camera.x += (kinematics_x.position - camera.x) * kinematics_x.velocity;
}

void Camera::updateY(units::MS elapsed_time) {
	const Accelerator* accelerator;

	accelerator = &kAccelerator;

	accelerator->updateVelocity(kinematics_y, elapsed_time);

	camera.y += (kinematics_y.position - camera.y) * kinematics_y.velocity;
}

void Camera::lookUp(units::Tile tiles) {
	camera.y -= units::tileToPixel(tiles) * kinematics_y.velocity;
}

void Camera::lookDown(units::Tile tiles) {
	camera.y += units::tileToPixel(tiles) * kinematics_y.velocity;
}

void Camera::lookLeft(units::Tile tiles) {
	camera.x -= units::tileToPixel(tiles) * kinematics_x.velocity;
}

void Camera::lookRight(units::Tile tiles) {
	camera.x += units::tileToPixel(tiles) * kinematics_x.velocity;
}
