#pragma once
#include <chrono>

class Timer
{

 public:

	explicit Timer(const int &interval);

	bool expired() const;
	void Reset();

 private:

	typedef std::chrono::time_point<std::chrono::steady_clock> Time;
	typedef std::chrono::high_resolution_clock Clock;

	long long interval_;
	long long last_tick_;

	long long current() const;

};

