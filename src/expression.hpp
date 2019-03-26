#pragma once
#include <type_traits>
#include <utility>
#include <math.h>

template <auto Fn>
class expression
{
public:
	template <class T>
	auto evaluate(const T value) 
		const noexcept -> decltype(Fn(value))
	{
		return Fn(value);
	}

	template <class T>
	auto bisection(const std::pair<T, T> interval) 
		const noexcept -> decltype(Fn(interval.first))
	{
		// COPY INTERVAL VALUES AND UNPACK USING STRUCTURED BINDINGS
		auto [begin, end] = interval;

		while (true)
		{
			// CALCULATE MIDPOINT
			const auto mid_point = (begin + end) / 2.0;
			
			// CHECK PRECISION
			constexpr auto convergence = 0.1; // DECREASE TO INCREASE PRECISION-LEEWAY
			if (std::abs(mid_point - begin) < convergence)
				break; // MID POINT WAS NEVER FOUND

			// CHECK SIGN CHANGE
			const auto mid_point_evaluation = Fn(mid_point);

			// FOUND ROOT?
			if (mid_point_evaluation == 0.00)
				return mid_point;

			// UPDATE INTERVAL
			const auto begin_evaluation = Fn(begin);
			if (std::signbit(begin_evaluation) == std::signbit(mid_point_evaluation))
			{
				begin = mid_point;
			}
			else
			{
				end = mid_point;
			}

		}
		
		return T{INFINITY};
	}
};