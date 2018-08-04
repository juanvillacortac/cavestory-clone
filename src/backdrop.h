#ifndef BACKDROP_H_
#define BACKDROP_H_

#include "graphics.h"

#include <string>

class Backdrop {
	public:
		virtual void draw(Graphics& graphics) const = 0;
};

class FixedBackdrop : public Backdrop {
	private:
		Graphics::SurfaceID surface_id_;
	public:
		FixedBackdrop(const std::string& path, Graphics& graphics);
		void draw(Graphics& graphics) const;
};

#endif // BACKDROP_H_
