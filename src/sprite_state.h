#ifndef SPRITE_STATE_H_
#define SPRITE_STATE_H_

#include <map>
#include <memory>
#include <tuple>

#define ENUM_FOREACH(var, enum_name) \
	for (int var = FIRST_##enum_name; var < LAST_##enum_name; ++var)

enum HorizontalFacing {
	FIRST_HORIZONTAL_FACING,
	LEFT = FIRST_HORIZONTAL_FACING,
	RIGHT,
	LAST_HORIZONTAL_FACING,
};

enum VerticalFacing {
	FIRST_VERTICAL_FACING,
	UP = FIRST_VERTICAL_FACING,
	DOWN,
	HORIZONTAL,
	LAST_VERTICAL_FACING,
};

#endif // SPRITE_STATE_H_
