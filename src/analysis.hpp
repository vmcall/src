#pragma once
#include <iostream>
#include "expression.hpp"
#include "test_case.hpp"
#include "timer.hpp"

class analysis
{
	using my_precision_t = double;

public:
	static inline auto test_precision()
		noexcept -> void
	{
		const auto expr = expression<test_case::two<my_precision_t>>();
		constexpr auto value = 12.345678;
		constexpr auto real_derivative = 456.247295839052;

		const auto base = std::sqrt(std::numeric_limits<double>::epsilon());

		auto min_precision = 1.0;
		auto best_delta = expr.derivative(value);

		for (double i = -0.0000001; i < 0.0000001; i += std::numeric_limits<double>::epsilon())
		{
			const auto derivative = expr.derivative_2(value, base + i);
			const auto precision = std::abs(real_derivative - derivative);

			if (precision < min_precision)
			{
				min_precision = precision;
				best_delta = base + i;
			}
		}
		
		printf("[Real]      %.15f\n", real_derivative);
		printf("[Brute]     %.15f\n", expr.derivative_2(value, best_delta));
		printf("[Precision] %.15f\n", min_precision);
		printf("[Delta]	    %.15f\n", best_delta);
	}

	static inline auto first()
		noexcept -> void
	{
		std::printf("Testing x^2\n");

		const auto expr = expression<test_case::one<my_precision_t>>();

		// TIME NEWTON RAPHSON
		const auto[time_newton_raphson, result_newton_raphson] = timer(
			[&](const my_precision_t val) 
				-> my_precision_t
		{
			return expr.newton_raphson(val);
		}).time<std::chrono::nanoseconds>(1.00);

		// TIME BISECTION
		const auto[time_bisection, result_bisection] = timer(
			[&](const std::pair<my_precision_t, my_precision_t> val) 
				-> my_precision_t
		{
			return expr.bisection(val);
		}).time<std::chrono::nanoseconds>( std::make_pair(-6.0, 2.0) );

		// PRINT
		std::printf(" [Bisection]      %.10f - Took %lld ns\n", result_bisection, time_bisection.count());
		std::printf(" [Newton-Raphson] %.10f - Took %lld ns\n", result_newton_raphson, time_newton_raphson.count());
	}

	static inline auto second()
		noexcept -> void
	{
		std::printf("Testing x^3 - x - 2\n");

		const auto expr = expression<test_case::two<my_precision_t>>();


		for (double i = 1.0; i < 100; i++)
		{
			// TIME NEWTON RAPHSON
			const auto[time_newton_raphson, result_newton_raphson] = timer(
				[&](const my_precision_t val)
				-> my_precision_t
			{
				return expr.newton_raphson(val);
			}).time<std::chrono::nanoseconds>(i);

			std::printf("%.0f;%lld\n", i, time_newton_raphson.count());
		}



		// TIME BISECTION
		const auto[time_bisection, result_bisection] = timer(
			[&](const std::pair<my_precision_t, my_precision_t> val)
			-> my_precision_t
		{
			return expr.bisection(val);
		}).time<std::chrono::nanoseconds>(std::make_pair(1.0, 2.0));

		// PRINT
		std::printf(" [Bisection]      %.10f - Took %lld ns\n", result_bisection, time_bisection.count());
		//std::printf(" [Newton-Raphson] %.10f - Took %lld ns\n", result_newton_raphson, time_newton_raphson.count());
	}

	static inline auto third()
		noexcept -> void
	{
		std::printf("Testing cbroot(x)\n");

		const auto expr = expression<test_case::three<my_precision_t>>();

		// TIME BISECTION
		const auto[time_bisection, result_bisection] = timer(
			[&](const std::pair<my_precision_t, my_precision_t> val)
			-> my_precision_t
		{
			return expr.bisection(val);
		}).time<std::chrono::nanoseconds>(std::make_pair(-1.0, 1.0));


		// PRINT
		std::printf(" [Bisection]      %.10f - Took %lld ns\n", result_bisection, time_bisection.count());
	}
};