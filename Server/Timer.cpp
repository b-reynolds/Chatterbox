#include "Timer.h"

Timer::Timer(const int& interval)
{
	this->interval = interval;
	lastTick = getTime();
}

bool Timer::hasExpired() const
{
	return getTime() - lastTick > interval;
}

void Timer::reset()
{
	lastTick = getTime();
}

long long Timer::getTime() const
{
	return std::chrono::duration_cast<std::chrono::seconds>(Clock::now().time_since_epoch()).count();
}
