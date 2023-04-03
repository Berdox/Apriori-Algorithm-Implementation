
#ifndef TIMER_H_INCLUDE
#define TIMER_H_INCLUDE

#include <chrono>

class Timer
{
public:
    Timer() {
        start = std::chrono::steady_clock::now();
    }
	double elapsed() const
	{
		return std::chrono::duration_cast<Second>(std::chrono::steady_clock::now() - start).count();
	}

private:
	using Second = std::chrono::duration<double, std::ratio<1>>;
    std::chrono::time_point<std::chrono::steady_clock> start;
};

#endif