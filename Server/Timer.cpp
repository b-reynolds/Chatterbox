#include "timer.h"

Timer::Timer(const int& interval)
{
	interval_ = interval;
	last_tick_ = current();
}

bool Timer::expired() const
{
	return current() - last_tick_ > interval_;
}

void Timer::Reset()
{
	last_tick_ = current();
}

long long Timer::current() const
{
	return std::chrono::duration_cast<std::chrono::seconds>(Clock::now().time_since_epoch()).count();
}
