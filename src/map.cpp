#include "map.h"
#include "sprite.h"
#include "graphics.h"
#include "game.h"
#include "rectangle.h"

#include <map>

using namespace tiles;

using std::shared_ptr;
using std::vector;

void Map::drawBackground(Graphics& graphics, SDL_Rect& camera) const {
	backdrop_->draw(graphics, camera);
	for (size_t row = 0; row < bkg_tiles_.size(); row++) {
		for (size_t col = 0; col < bkg_tiles_[row].size(); col++) {
			if (bkg_tiles_[row][col]) {
				bkg_tiles_[row][col]->draw(
						graphics,
						units::tileToGame(col), units::tileToGame(row), &camera);
			}
		}
	}
}

void Map::draw(Graphics& graphics, SDL_Rect& camera) const {
	for (size_t row = 0; row < tiles_.size(); row++) {
		for (size_t col = 0; col < tiles_[row].size(); col++) {
			if (tiles_[row][col].sprite) {
				tiles_[row][col].sprite->draw(
						graphics,
						units::tileToGame(col), units::tileToGame(row), &camera);
			}
		}
	}
}

vector<CollisionTile> Map::getCollidingTiles(
		const Rectangle& rectangle,
		sides::SideType direction) const {
	const units::Tile first_primary =
		units::gameToTile(rectangle.side(sides::opposite_side(direction)));
	const units::Tile last_primary =
		units::gameToTile(rectangle.side(direction));
	const units::Tile primary_incr =
		sides::is_max(direction) ?  1 : -1;

	const bool horizontal = sides::horizontal(direction);

	const units::Tile s_min =
		units::gameToTile(horizontal ? rectangle.top() : rectangle.left());
	const units::Tile s_mid =
		units::gameToTile(horizontal ? rectangle.center_y() : rectangle.center_x());
	const units::Tile s_max =
		units::gameToTile(horizontal ? rectangle.bottom() : rectangle.right());

	const bool s_positive = s_mid - s_min < s_max - s_mid;

	const units::Tile secondary_incr = s_positive ? 1 : -1;
	const units::Tile first_secondary = s_positive ? s_min : s_max;
	const units::Tile last_secondary = !s_positive ? s_min : s_max;

	vector<CollisionTile> collision_tiles;

	for (units::Tile primary = first_primary;
			primary != last_primary + primary_incr;
			primary += primary_incr) {
		for (units::Tile secondary = first_secondary;
				secondary != last_secondary + secondary_incr;
				secondary += secondary_incr) {
			const units::Tile row = !horizontal ? primary : secondary;
			const units::Tile col = horizontal ? primary : secondary;

			if (row <= tiles_.size() && col <= tiles_[row].size()) {
				collision_tiles.push_back(CollisionTile(row, col, tiles_[row][col].tile_type));
			}
		}
	}

	return collision_tiles;
}

Map* Map::createTestMap(Graphics& graphics) {
	Map* map = new Map();

	map->num_rows_ = 30; // 15 * 32 = 480
	map->num_cols_ = 40; // 20 * 32 = 640

	units::Tile num_rows = map->num_rows_;
	units::Tile num_cols = map->num_cols_;

	map->backdrop_.reset(new DinamicBackdrop("bkBlue", graphics, num_rows, num_cols, 2));

	// tiles_ && bkg_tiles_ are num_rows x num_cols in size
	map->tiles_ = vector<vector<Tile>>(
			num_rows, vector<Tile>(
				num_cols, Tile()
				)
			);
	map->bkg_tiles_ = vector<vector<shared_ptr<Sprite>>>(
			num_rows, vector<shared_ptr<Sprite>>(
				num_cols, shared_ptr<Sprite>()
				));

	map->tiles = {
		{ 33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34 },
		{ 49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50 },
		{ 33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,3,4,65,5,6,49,50,3,4,66,5,6,34,33,34,33,34,33,34,33,34,33,34 },
		{ 49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,36,0,0,0,0,0,65,66,0,0,0,0,0,66,5,6,49,50,49,50,49,50,49,50 },
		{ 33,34,33,34,33,34,33,34,33,34,33,34,33,34,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,6,33,3,4,37,33,34 },
		{ 49,50,49,50,49,50,49,50,49,50,49,50,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,66,0,0,35,49,50 },
		{ 33,34,33,34,33,34,33,34,33,34,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,51,33,34 },
		{ 49,50,49,50,49,50,49,50,49,50,54,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,35,49,50 },
		{ 33,34,33,34,33,34,33,34,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,51,33,34 },
		{ 49,50,49,50,49,50,49,50,54,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,22,49,50 },
		{ 33,34,33,34,33,34,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,51,33,34,33,34 },
		{ 49,50,49,50,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,22,19,20,21,22,49,50,49,50 },
		{ 33,34,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,22,33,34,33,34,33,34,33,34,33,34 },
		{ 49,50,38,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,22,49,50,49,50,49,50,49,50,49,50,49,50 },
		{ 33,34,54,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,35,33,34,33,34,33,34,33,34,33,34,33,34,33,34 },
		{ 49,50,54,0,0,65,66,65,66,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,51,49,50,49,50,49,50,49,50,49,50,49,50,49,50 },
		{ 33,34,54,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,5,6,33,34,33,34,33,34,33,34,33,34,33,34 },
		{ 49,50,52,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,65,0,0,0,0,0,5,6,49,50,49,50,49,50,49,50,49,50 },
		{ 33,34,33,19,20,0,0,0,0,0,2,3,4,66,5,6,2,0,0,0,0,0,0,0,0,0,0,0,0,51,33,34,33,34,33,34,33,34,33,34 },
		{ 49,50,49,50,49,38,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,37,50,49,50,49,50,49,50,49,50 },
		{ 33,34,33,34,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,66,5,6,33,34,33,34,33,34 },
		{ 49,50,49,50,38,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,6,49,50,49,50 },
		{ 33,34,33,34,19,20,0,0,0,0,0,0,0,2,0,0,0,0,0,18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,37,34,33,34 },
		{ 49,50,49,50,49,50,19,20,0,0,18,17,2,2,2,52,18,21,22,50,19,20,18,17,18,0,0,0,0,0,0,0,0,0,0,0,0,37,49,50 },
		{ 33,34,33,34,33,34,33,34,19,22,33,34,2,34,2,34,33,34,33,34,33,34,33,34,33,19,20,0,0,0,0,0,0,0,0,0,0,51,33,34 },
		{ 49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,19,20,21,22,19,20,0,0,0,0,53,49,50 },
		{ 33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,19,20,21,22,34,33,34 },
		{ 49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50 },
		{ 33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34,33,34 },
		{ 49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50,49,50 }
	};

	map->bkg_tiles = {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,44,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,44,0,0,0,0,0,45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,45,0,0,0,0,0,45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,44,0,45,0,0,0,0,0,45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,45,0,45,0,0,0,0,0,45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,45,0,45,0,0,0,0,0,45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,44,0,0,45,0,45,0,0,0,0,0,45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,45,0,0,45,0,45,0,0,0,0,0,45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,46,0,0,46,0,45,0,0,0,0,0,45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,45,0,0,0,0,0,45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,45,0,39,40,41,0,45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,46,0,55,72,57,0,46,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,0,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,44,0,0,0,0,0,44,0,0,0,0,32,0,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,45,0,0,0,0,0,47,0,0,0,0,32,0,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,45,0,0,0,0,0,0,0,0,16,0,32,0,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,47,0,0,0,0,0,0,0,0,48,0,32,0,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,48,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	};

	Tile block_wall(TileType().set(WALL), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(1), 0,
					units::tileToPixel(1), units::tileToPixel(1)
					)));

	// slope tiles

	enum {
		LTT, // Left Top Tall
		LTS, // Left Top Short
		RTS, // Right Top Short
		RTT, // Right Top Tall
		LBT, // Left Bottom Tall
		LBS, // Left Bottom Short
		RBS, // Right Bottom Short
		RBT, // Right Bottom Tall
		NUM_SLOPES
	};

	Tile slope_tile[NUM_SLOPES];

	for (int i = 0; i < NUM_SLOPES; i++) {
		slope_tile[i] = Tile(
				TileType().set(SLOPE).
				set(i / 2 % 2 == 0 ? LEFT_SLOPE : RIGHT_SLOPE).
				set(i / 4 == 0 ? TOP_SLOPE : BOTTOM_SLOPE).
				set((i + 1) / 2 % 2 == 0 ? TALL_SLOPE : SHORT_SLOPE),
				shared_ptr<Sprite>(new Sprite(
						graphics, "PrtCave",
						units::tileToPixel(2 + i % 4), units::tileToPixel(i / 4),
						units::tileToPixel(1), units::tileToPixel(1)
						)
					)
				);
	}

	// rock_wall

	enum {
		A,
		B,
		C,
		D,
		AA,
		BB,
		CC,
		DD,
		NUM_WALLS
	};

	Tile rock_wall[NUM_WALLS];

	rock_wall[A] = Tile(TileType().set(WALL), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(0), units::tileToPixel(2),
					units::tileToPixel(1), units::tileToPixel(1)
					)));
	rock_wall[B] = Tile(TileType().set(WALL), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(1), units::tileToPixel(2),
					units::tileToPixel(1), units::tileToPixel(1)
					)));
	rock_wall[C] = Tile(TileType().set(WALL), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(0), units::tileToPixel(3),
					units::tileToPixel(1), units::tileToPixel(1)
					)));
	rock_wall[D] = Tile(TileType().set(WALL), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(1), units::tileToPixel(3),
					units::tileToPixel(1), units::tileToPixel(1)
					)));
	rock_wall[AA] = Tile(TileType().set(EMPTY), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(0), units::tileToPixel(1),
					units::tileToPixel(1), units::tileToPixel(1)
					)));
	rock_wall[BB] = Tile(TileType().set(EMPTY), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(1), units::tileToPixel(1),
					units::tileToPixel(1), units::tileToPixel(1)
					)));
	rock_wall[CC] = Tile(TileType().set(EMPTY), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(0), units::tileToPixel(4),
					units::tileToPixel(1), units::tileToPixel(1)
					)));
	rock_wall[DD] = Tile(TileType().set(EMPTY), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(1), units::tileToPixel(4),
					units::tileToPixel(1), units::tileToPixel(1)
					)));

	// bounding_rock_wall

	Tile bounding_rock_wall[NUM_WALLS];

	bounding_rock_wall[A] = Tile(TileType().set(EMPTY), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(3), units::tileToPixel(2),
					units::tileToPixel(1), units::tileToPixel(1)
					)));
	bounding_rock_wall[B] = Tile(TileType().set(EMPTY), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(4), units::tileToPixel(2),
					units::tileToPixel(1), units::tileToPixel(1)
					)));
	bounding_rock_wall[C] = Tile(TileType().set(EMPTY), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(3), units::tileToPixel(3),
					units::tileToPixel(1), units::tileToPixel(1)
					)));
	bounding_rock_wall[D] = Tile(TileType().set(EMPTY), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(4), units::tileToPixel(3),
					units::tileToPixel(1), units::tileToPixel(1)
					)));
	bounding_rock_wall[AA] = Tile(TileType().set(EMPTY), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(2), units::tileToPixel(2),
					units::tileToPixel(1), units::tileToPixel(1)
					)));
	bounding_rock_wall[BB] = Tile(TileType().set(EMPTY), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(5), units::tileToPixel(2),
					units::tileToPixel(1), units::tileToPixel(1)
					)));
	bounding_rock_wall[CC] = Tile(TileType().set(EMPTY), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(2), units::tileToPixel(3),
					units::tileToPixel(1), units::tileToPixel(1)
					)));
	bounding_rock_wall[DD] = Tile(TileType().set(EMPTY), shared_ptr<Sprite>(new Sprite(
					graphics,
					"PrtCave",
					units::tileToPixel(5), units::tileToPixel(3),
					units::tileToPixel(1), units::tileToPixel(1)
					)));

	for (size_t i = 0; i < map->tiles.size(); i++) {
		for (size_t j = 0; j < map->tiles[i].size(); j++) {
			int x = map->tiles[i][j];

			switch (x) {
				// block wall
				case 2:
					map->tiles_[i][j] = block_wall;
					break;

				// slopes
				case 3:
					map->tiles_[i][j] = slope_tile[LTT];
					break;
				case 4:
					map->tiles_[i][j] = slope_tile[LTS];
					break;
				case 5:
					map->tiles_[i][j] = slope_tile[RTS];
					break;
				case 19:
					map->tiles_[i][j] = slope_tile[LBT];
					break;
				case 20:
					map->tiles_[i][j] = slope_tile[LBS];
					break;
				case 21:
					map->tiles_[i][j] = slope_tile[RBS];
					break;
				case 22:
					map->tiles_[i][j] = slope_tile[RBT];
					break;
				case 6:
					map->tiles_[i][j] = slope_tile[RTT];
					break;

				// rock_wall
				case 33:
					map->tiles_[i][j] = rock_wall[A];
					break;
				case 34:
					map->tiles_[i][j] = rock_wall[B];
					break;
				case 49:
					map->tiles_[i][j] = rock_wall[C];
					break;
				case 50:
					map->tiles_[i][j] = rock_wall[D];
					break;
				case 17:
					map->tiles_[i][j] = rock_wall[AA];
					break;
				case 18:
					map->tiles_[i][j] = rock_wall[BB];
					break;
				case 65:
					map->tiles_[i][j] = rock_wall[CC];
					break;
				case 66:
					map->tiles_[i][j] = rock_wall[DD];
					break;

				// bounding_rock_wall
				case 36:
					map->tiles_[i][j] = bounding_rock_wall[A];
					break;
				case 37:
					map->tiles_[i][j] = bounding_rock_wall[B];
					break;
				case 52:
					map->tiles_[i][j] = bounding_rock_wall[C];
					break;
				case 53:
					map->tiles_[i][j] = bounding_rock_wall[D];
					break;
				case 35:
					map->tiles_[i][j] = bounding_rock_wall[AA];
					break;
				case 38:
					map->tiles_[i][j] = bounding_rock_wall[BB];
					break;
				case 51:
					map->tiles_[i][j] = bounding_rock_wall[CC];
					break;
				case 54:
					map->tiles_[i][j] = bounding_rock_wall[DD];
					break;
			}
		}
	}

	// chain bkg

	vector<shared_ptr<Sprite>> chain(4);

	chain = {
		shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(11), units::tileToPixel(2),
				units::tileToPixel(1), units::tileToPixel(1)
				)),
		shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(12), units::tileToPixel(2),
				units::tileToPixel(1), units::tileToPixel(1)
				)),
		shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(13), units::tileToPixel(2),
				units::tileToPixel(1), units::tileToPixel(1)
				)),
		shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(14), units::tileToPixel(2),
				units::tileToPixel(1), units::tileToPixel(1)
				))
	};

	// bars bkg

	vector<shared_ptr<Sprite>> bars(3);

	bars = {
		shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(15), units::tileToPixel(0),
				units::tileToPixel(1), units::tileToPixel(1)
				)),
		shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(15), units::tileToPixel(1),
				units::tileToPixel(1), units::tileToPixel(1)
				)),
		shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(15), units::tileToPixel(2),
				units::tileToPixel(1), units::tileToPixel(1)
				))
	};

	// tiger bkg

	enum {
		LT,
		MT,
		RT,
		LB,
		MB,
		RB,
		TIGER_TILES
	};

	vector<shared_ptr<Sprite>> tiger(TIGER_TILES);

	tiger = {
		shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(6), units::tileToPixel(2),
				units::tileToPixel(1), units::tileToPixel(1)
				)),
		shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(7), units::tileToPixel(2),
				units::tileToPixel(1), units::tileToPixel(1)
				)),
		shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(8), units::tileToPixel(2),
				units::tileToPixel(1), units::tileToPixel(1)
				)),
		shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(6), units::tileToPixel(3),
				units::tileToPixel(1), units::tileToPixel(1)
				)),
		shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(7), units::tileToPixel(4),
				units::tileToPixel(1), units::tileToPixel(1)
				)),
		shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(8), units::tileToPixel(3),
				units::tileToPixel(1), units::tileToPixel(1)
				))
	};

	for (size_t i = 0; i < map->bkg_tiles.size(); i++) {
		for (size_t j = 0; j < map->bkg_tiles[i].size(); j++) {
			int x = map->bkg_tiles[i][j];

			switch (x) {
				// chains
				case 44:
					map->bkg_tiles_[i][j] = chain[0];
					break;
				case 45:
					map->bkg_tiles_[i][j] = chain[1];
					break;
				case 46:
					map->bkg_tiles_[i][j] = chain[2];
					break;
				case 47:
					map->bkg_tiles_[i][j] = chain[3];
					break;

				// bars
				case 16:
					map->bkg_tiles_[i][j] = bars[0];
					break;
				case 32:
					map->bkg_tiles_[i][j] = bars[1];
					break;
				case 48:
					map->bkg_tiles_[i][j] = bars[2];
					break;

				// tiger
				case 39:
					map->bkg_tiles_[i][j] = tiger[LT];
					break;
				case 40:
					map->bkg_tiles_[i][j] = tiger[MT];
					break;
				case 41:
					map->bkg_tiles_[i][j] = tiger[RT];
					break;
				case 55:
					map->bkg_tiles_[i][j] = tiger[LB];
					break;
				case 72:
					map->bkg_tiles_[i][j] = tiger[MB];
					break;
				case 57:
					map->bkg_tiles_[i][j] = tiger[RB];
					break;
			}
		}
	}

	return map;
}
