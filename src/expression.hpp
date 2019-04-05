#pragma once
#include <type_traits>
#include <utility>
#include <limits>
#include <math.h>

template <auto Fn>
class expression
{
public:
	// NUMBER OF SIGNIFICANT DIGITS IN OPERATIONS
	constexpr static auto PRECISION = 0.00000000000001; // 15 DIGITS FOR DOUBLE

	// EVALUATE THE EXPRESSION WITH AN ARBITRARY VARIABLE
	template <class T>
	auto evaluate(const T value) 
		const noexcept -> decltype(Fn(value))
	{
		return Fn(value);
	}

	// CALCULATE DERIVATIVE
	template <class T>
	auto inline derivative_2(const T value, const T delta)
		const noexcept -> decltype(Fn(value))
	{
		// CALCULATE SLOPE
		return (Fn(value + delta) - Fn(value)) / delta;
	}

	// CALCULATE DERIVATIVE
	template <class T>
	auto inline derivative(const T value) 
		const noexcept -> decltype(Fn(value))
	{
		// SMALLEST POSSIBLE CHANGE IN A DOUBLE
		const auto delta = std::sqrt( std::numeric_limits<T>::epsilon() ); 

		// CALCULATE SLOPE
		return (Fn(value + delta) - Fn(value)) / delta;
	} 

	// NEWTON-RAPHSON
	template <class T>
	auto inline newton_raphson(const T value)
		const noexcept -> decltype(Fn(value))
	{
		// CALCULATE NEW VALUE FROM THE FORMULA
		// N_A+1 = N_A - F(N_A)/F'(N_A)
		const auto new_value = value - (Fn(value) / this->derivative(value));

		auto has_acceptable_precision = [](T x, T y) -> T
		{
			return std::abs(x - y) < PRECISION;
		};

		// RETURN WHEN RESULT IS SUFFICIENTLY PRECISE
		if (has_acceptable_precision(value, new_value))
			return new_value;

		// ITERATE
		return this->newton_raphson(new_value);
	}

	// BISECTION
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
		if (std::abs(mid) < PRECISION)
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