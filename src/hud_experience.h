#ifndef HUD_EXPERIENCE_H_
#define HUD_EXPERIENCE_H_

#include "sprite.h"
#include "units.h"
#include "timer.h"
#include "varying_width_spr.h"

class ExperienceHUD {
	private:
		Sprite experience_bar_sprite_, level_sprite_, flash_sprite_, max_sprite_;
		Timer flash_timer_;
		VaryingWidthSprite fill_sprite_;
	public:
		ExperienceHUD(Graphics& graphics);

		void activateFlash() { flash_timer_.reset(); }
		void draw(Graphics& graphics,
				units::GunLevel gun_level,
				units::GunExperience current_experience,
				units::GunExperience level_experience);
};

#endif // HUD_EXPERIENCE_H_
