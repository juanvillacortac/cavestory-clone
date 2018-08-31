#ifndef HUD_EXPERIENCE_H_
#define HUD_EXPERIENCE_H_

#include "sprite.h"
#include "units.h"

class ExperienceHUD {
	private:
		Sprite experience_bar_sprite_, level_sprite_;
	public:
		ExperienceHUD(Graphics& graphics);

		void draw(Graphics& graphics, units::GunLevel gun_level);
};

#endif // HUD_EXPERIENCE_H_
