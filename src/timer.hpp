#pragma once
#include <chrono>

template <auto Fn>
class timer
{
public:
	template <class T, class ...U>
	auto time(const U... args) 
		const noexcept -> T
	{
		// GET MONOTONIC CLOCK TIME
		const auto start_time = std::chrono::steady_clock::now();

		// RUN FUNCTION
		Fn(args...);

		// GET MONOTONIC CLOCK TIME AGAIN
		const auto end_time = std::chrono::steady_clock::now();

		// RETURN THE TIME DELTA IN PREFERED, ARBITRARY TYPE
		return std::chrono::duration_cast<T>(end_time - start_time);
	}
};