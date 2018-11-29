#ifndef BACKDROP_H_
#define BACKDROP_H_

#include "graphics.h"
#include "units.h"

#include <string>

class Backdrop {
	public:
		virtual ~Backdrop() {}

		virtual void draw(Graphics& graphics, SDL_Rect& camera) const = 0;
};

class FixedBackdrop : public Backdrop {
	private:
		Graphics::SurfaceID surface_id_;

		units::Tile rows_, cols_;
	public:
		~FixedBackdrop() {}

		FixedBackdrop(
				const std::string& path,
				Graphics& graphics,
				units::Tile rows, units::Tile cols);
		void draw(Graphics& graphics, SDL_Rect& camera) const;
};

class DinamicBackdrop : public Backdrop {
	private:
		Graphics::SurfaceID surface_id_;

		units::Tile rows_, cols_;

		float profundity_;
	public:
		~DinamicBackdrop() {}

		DinamicBackdrop(
				const std::string& path,
				Graphics& graphics,
				units::Tile rows, units::Tile cols,
				float profundity);
		void draw(Graphics& graphics, SDL_Rect& camera) const;
};

#endif // BACKDROP_H_
