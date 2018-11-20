#ifndef DAMAGE_TEXTS_H_
#define DAMAGE_TEXTS_H_

#include "units.h"

#include <memory>
#include <map>

struct FloatingNumber;
struct Damageable;
struct Graphics;
struct SDL_Rect;

class DamageTexts {
	private:
		typedef std::map<std::shared_ptr<FloatingNumber>, std::weak_ptr<Damageable>> DamageTextMap;

		DamageTextMap damage_text_map_;
	public:
		void addDamageable(std::shared_ptr<Damageable> damageable);
		void update(units::MS elapsed_time_ms);
		void draw(Graphics& graphics, SDL_Rect& camera);
};

#endif // DAMAGE_TEXTS_H_
