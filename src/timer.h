#ifndef TIMER_H_
#define TIMER_H_

#include "units.h"

#include <set>
#include <boost/noncopyable.hpp>

class Timer : private boost::noncopyable {
	private:
		void update(units::MS elapsed_time_ms) {
			if(active())
				current_time_ += elapsed_time_ms;
		}

		units::MS current_time_;
		const units::MS expiration_time_;

		static std::set<Timer*> timers_;
	public:
		Timer(units::MS expiration_time) :
			current_time_(expiration_time + 1),
			expiration_time_(expiration_time) { timers_.insert(this); }
		~Timer() { timers_.erase(this); }

		void reset() { current_time_ = 0; }
		bool active() const { return current_time_ < expiration_time_; }
		bool expired() const { return !active(); }

		// Assumes the user knows if |this| is active or not.
		units::MS current_time() const { return current_time_; }

		static void updateAll(units::MS elapsed_time_ms);
};

#endif // TIMER_H_
