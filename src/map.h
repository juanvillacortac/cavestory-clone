#ifndef MAP_H_
#define MAP_H_

#include "backdrop.h"
#include "units.h"
#include "collision_tile.h"
#include "tile_type.h"

#include <memory>
#include <vector>

struct Graphics;
struct Sprite;
struct Rectangle;

class Map {
	public:
		static Map* createTestMap(Graphics& graphics);

		std::vector<CollisionTile> getCollidingTiles(
				const Rectangle& rectangle,
				sides::SideType direction) const;

		void drawBackground(Graphics& graphics, SDL_Rect& camera) const;
		void draw(Graphics& graphics, SDL_Rect& camera) const;

		units::Tile rows() { return num_rows_; }
		units::Tile cols() { return num_cols_; }
	private:
		class Tile {
			public:
				Tile(tiles::TileType tile_type = tiles::TileType().set(tiles::EMPTY),
						std::shared_ptr<Sprite> sprite = std::shared_ptr<Sprite>()) :
					tile_type(tile_type),
					sprite(sprite) {}

				tiles::TileType tile_type;
				std::shared_ptr<Sprite> sprite;
		};

		std::unique_ptr<Backdrop> backdrop_;

		std::vector<std::vector<int>> bkg_tiles;
		std::vector<std::vector<int>> tiles;

		std::vector<std::vector<std::shared_ptr<Sprite>>> bkg_tiles_;
		std::vector<std::vector<Tile>> tiles_;

		units::Tile num_rows_;
		units::Tile num_cols_;
};

#endif // MAP_H_
