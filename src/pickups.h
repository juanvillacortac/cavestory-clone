#ifndef PICKUPS_H_
#define PICKUPS_H_

#include "units.h"

#include <memory>
#include <set>

struct Graphics;
struct Map;
struct Pickup;
struct Player;
struct SDL_Rect;

class Pickups {
	private:
		typedef std::set<std::shared_ptr<Pickup> > PickupSet;
		PickupSet pickups_;
	public:
		void add(std::shared_ptr<Pickup> pickup) { pickups_.insert(pickup); }
		void handleCollision(Player& player);
		void update(units::MS elapsed_time, const Map& map);
		void draw(Graphics& graphics, SDL_Rect& camera);
};

#endif // PICKUPS_H_ 
