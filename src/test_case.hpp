#pragma once
#include <math.h>

class test_case
{
public:

	// x^2 
	template <class T>
	static auto one(const T value) -> T
	{
		return std::pow(value, T{ 2 });
	}

	// x^3 - x - 2
	template <class T>
	static auto two(const T value) -> T
	{
		return std::pow(value, T{3}) - value - T{2};
	}

	// cbrt(x)
	template <class T>
	static auto three(const T value) -> T
	{
		return std::cbrt(value);
	}
};