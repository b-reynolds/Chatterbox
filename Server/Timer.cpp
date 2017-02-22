#include "timer.h"

Timer::Timer(const int& interval)
{
	interval_ = interval;
	last_tick_ = get_current_time();
}

bool Timer::has_expired() const
{
	return get_current_time() - last_tick_ > interval_;
}

void Timer::Reset()
{
	last_tick_ = get_current_time();
}

long long Timer::get_current_time() const
{
	return std::chrono::duration_cast<std::chrono::seconds>(Clock::now().time_since_epoch()).count();
}
