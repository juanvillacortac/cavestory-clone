#include "map.h"
#include "sprite.h"
#include "graphics.h"
#include "game.h"
#include "rectangle.h"

using boost::shared_ptr;
using std::vector;

void Map::update(units::MS elapsed_time_ms) {
	for(size_t row = 0; row < tiles_.size(); row++) {
		for(size_t col = 0; col < tiles_[row].size(); col++) {
			if(tiles_[row][col].sprite) {
				tiles_[row][col].sprite->update(elapsed_time_ms);
			}
		}
	}
}

void Map::drawBackground(Graphics& graphics) const {
	backdrop_->draw(graphics);
	for(size_t row = 0; row < bkg_tiles_.size(); row++) {
		for(size_t col = 0; col < bkg_tiles_[row].size(); col++) {
			if(bkg_tiles_[row][col]) {
				bkg_tiles_[row][col]->draw(
						graphics,
						col * Game::kTileSize, row * Game::kTileSize);
			}
		}
	}
}

void Map::draw(Graphics& graphics) const {
	for(size_t row = 0; row < tiles_.size(); row++) {
		for(size_t col = 0; col < tiles_[row].size(); col++) {
			if(tiles_[row][col].sprite) {
				tiles_[row][col].sprite->draw(
						graphics,
						col * Game::kTileSize, row * Game::kTileSize);
			}
		}
	}
}

vector<Map::CollisionTile> Map::getCollidingTiles(const Rectangle& rectangle) const {
	const int first_row = rectangle.top() / Game::kTileSize;
	const int last_row = rectangle.bottom() / Game::kTileSize;
	const int first_col = rectangle.left() / Game::kTileSize;
	const int last_col = rectangle.right() / Game::kTileSize;

	vector<CollisionTile> collision_tiles;

	for(int row = first_row; row <= last_row; row++) {
		for(int col = first_col; col <= last_col; col++) {
			collision_tiles.push_back(CollisionTile(row, col, tiles_[row][col].tile_type));
		}
	}

	return collision_tiles;
}

Map* Map::createTestMap(Graphics& graphics) {
	Map* map = new Map();

	map->backdrop_.reset(new FixedBackdrop("assets/bkBlue.bmp", graphics));

	const int num_rows = 15; // 15 * 32 = 480
	const int num_cols = 20; // 20 * 32 = 640

	// tiles_ && bkg_tiles_ are num_rows x num_cols in size
	map->tiles_ = vector<vector<Tile>>(
			num_rows, vector<Tile>(
				num_cols, Tile()
				)
			);
	map->bkg_tiles_ = vector<vector<shared_ptr<Sprite>>>(
			num_rows, vector<shared_ptr<Sprite>>(
				num_cols, shared_ptr<Sprite>()
				)
			);

	shared_ptr<Sprite> sprite(new Sprite(
				graphics,
				"assets/PrtCave.bmp",
				Game::kTileSize, 0,
				Game::kTileSize, Game::kTileSize));

	Tile tile(WALL_TILE, sprite);

	for(int col = 0; col < num_cols; col++) {
		for(int row = 11; row < num_rows; row++) {
			map->tiles_[row][col] = tile;
		}
	}

	map->tiles_[10][5] = tile;
	map->tiles_[10][7] = tile;
	map->tiles_[9][6] = tile;
	map->tiles_[10][6] = tile;
	map->tiles_[7][12] = tile;

	// Chains stuff
	shared_ptr<Sprite> chain_top(new Sprite(
				graphics,
				"assets/PrtCave.bmp",
				11 * Game::kTileSize, 2 * Game::kTileSize,
				Game::kTileSize, Game::kTileSize));
	shared_ptr<Sprite> chain_body(new Sprite(
				graphics,
				"assets/PrtCave.bmp",
				12 * Game::kTileSize, 2 * Game::kTileSize,
				Game::kTileSize, Game::kTileSize));
	shared_ptr<Sprite> chain_bottom(new Sprite(
				graphics,
				"assets/PrtCave.bmp",
				13 * Game::kTileSize, 2 * Game::kTileSize,
				Game::kTileSize, Game::kTileSize));

	map->bkg_tiles_[8][12] = chain_top;
	map->bkg_tiles_[9][12] = chain_body;
	map->bkg_tiles_[10][12] = chain_bottom;

	return map;
}
