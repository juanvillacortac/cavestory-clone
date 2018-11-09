#ifndef DAMAGEABLE_H_
#define DAMAGEABLE_H_

#include "units.h"

#include <memory>

struct FloatingNumber;

class Damageable {
	public:
		virtual ~Damageable() = 0;

		virtual units::Game center_x() const = 0;
		virtual units::Game center_y() const = 0;
		virtual std::shared_ptr<FloatingNumber> get_damage_text() = 0;
};

inline Damageable::~Damageable() {}

#endif // DAMAGEABLE_H_
