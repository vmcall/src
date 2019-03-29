#pragma once
#include <type_traits>
#include <utility>
#include <limits>
#include <math.h>

template <auto Fn>
class expression
{
public:
	// EVALUATE THE EXPRESSION WITH AN ARBITRARY VARIABLE
	template <class T>
	auto evaluate(const T value) 
		const noexcept -> decltype(Fn(value))
	{
		return Fn(value);
	}

	// CALCULATE DERIATIVE
	template <class T>
	auto inline deriative(const T value) 
		const noexcept -> decltype(Fn(value))
	{
		// SMALLEST POSSIBLE CHANGE IN A DOUBLE

		// REMEMBER TO DOCUMENT THIS
		const auto delta = std::sqrt( std::numeric_limits<double>::epsilon() ); // 1.49011611938476562e-8

		// CALCULATE SLOPE
		return (Fn(value + delta) - Fn(value)) / delta;
	}

	// NEWTON-RAPHSON
	template <class T>
	auto inline newton_raphson(const T value)
		const noexcept -> decltype(Fn(value))
	{
		// CALCULATE NEW VALUE
		const auto new_value = value - (Fn(value) / this->deriative(value));

		auto has_acceptable_precision = [](T x, T y) -> T
		{
			constexpr auto precision = 0.00000001; // DETERMINES EQUALITY PRECISION
			return std::abs(x - y) < precision;
		};

		if (has_acceptable_precision(value, new_value))
			return new_value;

		// NOT IMPLEMENTED
		return this->newton_raphson(new_value);
	}

	// BISECTION ANALYSIS
	template <class T>
	auto inline bisection(std::pair<T, T> interval) 
		const noexcept -> decltype(Fn(interval.first))
	{
		// UNPACK INTERVAL USING STRUCTURED BINDINGS
		auto& [begin, end] = interval;

		// CALCULATE MIDPOINT
		const auto mid_point = (begin + end) / 2.0;
		const auto mid = Fn(mid_point);

		// FOUND ROOT?
		constexpr auto precision = 0.00000001; // DECREASE TO INCREASE PRECISION-LEEWAY
		if (std::abs(mid) < precision)
			return mid_point;

		// CHECK SIGN CHANGE AND UPDATE INTERVAL
		const auto begin_eval = Fn(begin);
		if (std::signbit(begin_eval) == std::signbit(mid))
		{
			begin = mid_point;
		}
		else
		{
			end = mid_point;
		}

		return this->bisection<T>(interval);
	}
};