#include "Stopwatch.hpp"
using namespace std::chrono; // I am so sorry

#include <iostream>

template <class Clock>
Stopwatch<Clock>::Stopwatch() {
	running = false;
	prev_lap_sum = clock_duration(0);
	curr_lap_sum = clock_duration(0);
}

template <class Clock>
double Stopwatch<Clock>::totalTime() {
	duration<double> running_time = (running) ? (Clock::now() - run_time) : duration<double>(0);
	duration<double> total_time = running_time + curr_lap_sum + prev_lap_sum; 

	return total_time.count();
}

template <class Clock>
double Stopwatch<Clock>::lapTime() {
	duration<double> running_time = (running) ? (Clock::now() - run_time) : duration<double>(0);
	duration<double> lap_time = running_time + curr_lap_sum;

	return lap_time.count();
}

template <class Clock>
double Stopwatch<Clock>::start() {
	clock_time_point now = Clock::now();

	if (running) {
		duration<double> running_time = now - run_time;
		duration<double> lap_time = running_time + curr_lap_sum;

		return lap_time.count();
	}
	else {
		run_time = now;
		running = true;

		return 0;
	}
}

template <class Clock>
double Stopwatch<Clock>::stop() {
	clock_time_point now = Clock::now();

	if (running) {
		clock_duration running_time = now - run_time;
		curr_lap_sum += running_time;
		running = false;
	}

	duration<double> casted_curr_lap_sum = duration_cast<duration<double>>(curr_lap_sum);
	return casted_curr_lap_sum.count();
}

template <class Clock>
double Stopwatch<Clock>::startstop() {
	if (running) {
		return stop();
	}
	else {
		return start();
	}
}

template <class Clock>
double Stopwatch<Clock>::lap() {
	clock_time_point now = Clock::now();
	clock_duration running_time = (running) ? (now - run_time) : clock_duration(0);
	clock_duration lap_time = curr_lap_sum + running_time;
	prev_lap_sum += lap_time;
	curr_lap_sum = clock_duration(0);
	run_time = now;

	duration<double> casted_lap_time = duration_cast<duration<double>>(lap_time);
	return casted_lap_time.count();
}

template <class Clock>
double Stopwatch<Clock>::reset() {
	double lap_time = lapTime();

	running = false;
	prev_lap_sum = clock_duration(0);
	curr_lap_sum = clock_duration(0);

	return lap_time;
}