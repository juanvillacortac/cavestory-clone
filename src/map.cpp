#include "map.h"
#include "sprite.h"
#include "graphics.h"
#include "game.h"

using boost::shared_ptr;
using std::vector;

void Map::update(int elapsed_time_ms) {
	for(size_t row = 0; row < foreground_sprites_.size(); row++) {
		for(size_t col = 0; col < foreground_sprites_[row].size(); col++) {
			if(foreground_sprites_[row][col]) {
				foreground_sprites_[row][col]->update(elapsed_time_ms);
			}
		}
	}
}

void Map::draw(Graphics& graphics) const {
	for(size_t row = 0; row < foreground_sprites_.size(); row++) {
		for(size_t col = 0; col < foreground_sprites_[row].size(); col++) {
			if(foreground_sprites_[row][col]) {
				foreground_sprites_[row][col]->draw(
						graphics,
						col * Game::kTileSize, row * Game::kTileSize);
			}
		}
	}
}

Map* Map::createTestMap(Graphics& graphics) {
	Map* map = new Map();

	const int num_rows = 15; // 15 * 32 = 480
	const int num_cols = 20; // 20 * 32 = 640

	// foreground_sprites_ is num_rows x num_cols in size
	map->foreground_sprites_ = vector<vector<shared_ptr<Sprite>>>(
			num_rows, vector<shared_ptr<Sprite>>(
				num_cols, shared_ptr<Sprite>()
				)
			);

	const int row = 11;

	shared_ptr<Sprite> sprite(new Sprite(
				graphics,
				"assets/PrtCave.pbm",
				Game::kTileSize, 0,
				Game::kTileSize, Game::kTileSize));

	for(int col = 0; col < num_cols; col++) {
		map->foreground_sprites_[row][col] = sprite;
	}

	return map;
}
