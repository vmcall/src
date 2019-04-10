#pragma once
#include <type_traits>
#include <utility>
#include <limits>
#include <math.h>

#include "math_constant.hpp"

template <auto Fn>
class expression
{
public:
	// NUMBER OF SIGNIFICANT DIGITS IN OPERATIONS
	constexpr static auto PRECISION = math_constant::my_precision_t{0.000000000000001}; // 15 DIGITS FOR DOUBLE

	// EVALUATE THE EXPRESSION WITH AN ARBITRARY VARIABLE
	template <class T>
	auto evaluate(const T value) 
		const noexcept -> decltype(Fn(value))
	{
		return Fn(value);
	}

	// CALCULATE DERIVATIVE
	template <class T>
	auto inline derivative_custom(const T value, const T delta)
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
		// CALCULATE SLOPE
		return (Fn(value + math_constant::best_delta) - Fn(value)) / math_constant::best_delta;
	} 

	// NEWTON-RAPHSON
	template <class T>
	auto inline newton_raphson(const T value)
		const noexcept -> decltype(Fn(value))
	{
		// CALCULATE NEW VALUE FROM THE FORMULA
		// N_(A+1) = N_A - F(N_A)/F'(N_A)
		const auto new_value = value - (Fn(value) / this->derivative(value));

		// RETURN WHEN RESULT IS SUFFICIENTLY PRECISE
		if (std::abs(value - new_value) < PRECISION)
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
		const auto mid_point = (begin + end) / T{2.0};
		const auto mid = Fn(mid_point);

		// FOUND ROOT?
		if (std::abs(mid) < PRECISION)
			return mid_point;

		// CHECK SIGN CHANGE AND UPDATE INTERVAL
		const auto sign_changed = std::signbit(Fn(begin)) != std::signbit(mid);
		(sign_changed ? end : begin) = mid_point;

		return this->bisection<T>(interval);
	}
};