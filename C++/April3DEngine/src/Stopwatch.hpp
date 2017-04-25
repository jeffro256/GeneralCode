#ifndef _STOPWATCH_HPP_
#define _STOPWATCH_HPP_

#include <chrono>

template <class Clock = std::chrono::high_resolution_clock>
class Stopwatch {
public:
	using clock_duration = typename Clock::duration;
	using clock_time_point = typename Clock::time_point; 

	Stopwatch();

	double totalTime();
	double lapTime();

	double start();
	double stop();
	double startstop();
	double lap();
	double reset();

private:
	bool running;
	typename Clock::duration prev_lap_sum;
	typename Clock::duration curr_lap_sum;
	typename Clock::time_point run_time;
};

#include "Stopwatch.inl"

#endif