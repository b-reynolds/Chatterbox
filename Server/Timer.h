#pragma once
#include <chrono>

class Timer
{

	typedef std::chrono::time_point<std::chrono::steady_clock> Time;
	typedef std::chrono::high_resolution_clock Clock;

public:

	explicit Timer(const int &interval);

	bool hasExpired() const;
	void reset();

private:

	long long interval;
	long long lastTick;

	long long getTime() const;

};

