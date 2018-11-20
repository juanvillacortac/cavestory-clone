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

			if (row <= tiles_.size() && col <= tiles_[1].size()) {
				collision_tiles.push_back(CollisionTile(row, col, tiles_[row][col].tile_type));
			}
		}
	}

	return collision_tiles;
}

Map* Map::createTestMap(Graphics& graphics) {
	Map* map = new Map();

	map->backdrop_.reset(new FixedBackdrop("bkBlue", graphics));

	const units::Tile num_rows = 15; // 15 * 32 = 480
	const units::Tile num_cols = 20; // 20 * 32 = 640

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

	Tile wall_tile(TileType().set(WALL), shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(1), 0,
				units::tileToPixel(1), units::tileToPixel(1)
				)));

	Tile rock_tile(TileType().set(EMPTY), shared_ptr<Sprite>(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(0), units::tileToPixel(1),
				units::tileToPixel(1), units::tileToPixel(1)
				)));

	// Chains stuff
	shared_ptr<Sprite> chain_top(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(11), units::tileToPixel(2),
				units::tileToPixel(1), units::tileToPixel(1)
				));
	shared_ptr<Sprite> chain_body(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(12), units::tileToPixel(2),
				units::tileToPixel(1), units::tileToPixel(1)
				));
	shared_ptr<Sprite> chain_bottom(new Sprite(
				graphics,
				"PrtCave",
				units::tileToPixel(13), units::tileToPixel(2),
				units::tileToPixel(1), units::tileToPixel(1)
				));

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

	for (units::Tile col = 0; col < num_cols; col++) {
		for (units::Tile row = 12; row < num_rows; row++) {
			map->tiles_[row][col] = wall_tile;
		}
	}

	for (units::Tile col = 0; col < num_cols; col++)
		if (col < 13 || col > 17)
		map->tiles_[11][col] = wall_tile;

	map->tiles_[10][5] = wall_tile;
	map->tiles_[10][7] = wall_tile;
	map->tiles_[9][6] = wall_tile;
	map->tiles_[10][6] = wall_tile;
	map->tiles_[7][12] = wall_tile;

	map->tiles_[11][13] = slope_tile[LBT];
	map->tiles_[11][14] = slope_tile[LBS];

	map->tiles_[11][15] = rock_tile;

	map->tiles_[11][16] = slope_tile[RBS];
	map->tiles_[11][17] = slope_tile[RBT];

	int temp_row = 3;

	map->tiles_[5][temp_row] = wall_tile;
	map->tiles_[4][temp_row++] = wall_tile;
	map->tiles_[5][temp_row] = slope_tile[LTT];
	map->tiles_[4][temp_row++] = wall_tile;
	map->tiles_[5][temp_row] = slope_tile[LTS];
	map->tiles_[4][temp_row++] = wall_tile;
	map->tiles_[4][temp_row++] = wall_tile;
	map->tiles_[5][temp_row] = slope_tile[RTS];
	map->tiles_[4][temp_row++] = wall_tile;
	map->tiles_[5][temp_row] = slope_tile[RTT];
	map->tiles_[4][temp_row++] = wall_tile;
	map->tiles_[4][temp_row++] = wall_tile;
	map->tiles_[5][temp_row - 1] = wall_tile;

	map->bkg_tiles_[6][3] = chain_top;
	for (units::Tile col = 7; col <= 9; col++)
		map->bkg_tiles_[col][3] = chain_body;
	map->bkg_tiles_[10][3] = chain_bottom;

	map->bkg_tiles_[6][9] = chain_top;
	for (units::Tile col = 7; col <= 9; col++)
		map->bkg_tiles_[col][9] = chain_body;
	map->bkg_tiles_[10][9] = chain_bottom;

	map->bkg_tiles_[8][12] = chain_top;
	map->bkg_tiles_[9][12] = chain_body;
	map->bkg_tiles_[10][12] = chain_bottom;

	return map;
}
