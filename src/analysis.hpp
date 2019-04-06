#pragma once
#include <iostream>
#include "expression.hpp"
#include "test_case.hpp"
#include "timer.hpp"
#include "math_constant.hpp"

class analysis
{
public:
	static inline auto test_precision()
		noexcept -> void
	{
		// SET UP BASE DELTA
		const auto expr = expression<test_case::two<math_constant::my_precision_t>>();
		constexpr auto value = math_constant::my_precision_t{12.345678};					// ARBITRARY
		constexpr auto real_derivative = math_constant::my_precision_t{456.247295839052};	// CALCULATED BY WOLFRAM-ALPHA

		auto min_precision = math_constant::my_precision_t{1.0};
		auto bruteforced_delta = math_constant::best_delta;

		constexpr auto desired_precision = math_constant::my_precision_t{0.00000001};
		for (auto i = -desired_precision;
				  i < desired_precision;
				  i += std::numeric_limits<math_constant::my_precision_t>::epsilon())
		{
			const auto derivative = expr.derivative_2(value, math_constant::best_delta + i);
			const auto precision = std::abs(real_derivative - derivative);

			if (precision < min_precision)
			{
				min_precision = precision;
				bruteforced_delta = math_constant::best_delta + i;
			}
		}
		
		printf("[Real]      %.15f\n", real_derivative);
		printf("[Brute]     %.15f\n", expr.derivative_2(value, bruteforced_delta));
		printf("[Precision] %.15f\n", min_precision);
		printf("[Delta]	    %.15f\n", bruteforced_delta);

		math_constant::best_delta = bruteforced_delta;
	}

	static inline auto first()
		noexcept -> void
	{
		std::printf("Testing x^2\n");

		const auto expr = expression<test_case::one<math_constant::my_precision_t>>();

		// TIME NEWTON RAPHSON
		const auto[time_newton_raphson, result_newton_raphson] = timer(
			[&](const math_constant::my_precision_t val)
				-> math_constant::my_precision_t
		{
			return expr.newton_raphson(val);
		}).time<std::chrono::nanoseconds>(1.00);

		// TIME BISECTION
		const auto[time_bisection, result_bisection] = timer(
			[&](const std::pair<math_constant::my_precision_t, math_constant::my_precision_t> val)
				-> math_constant::my_precision_t
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

		const auto expr = expression<test_case::two<math_constant::my_precision_t>>();


		//for (double i = 1.0; i < 100; i++)
		//{
		//	// TIME NEWTON RAPHSON
		//	const auto[time_newton_raphson, result_newton_raphson] = timer(
		//		[&](const math_constant::my_precision_t val)
		//		-> math_constant::my_precision_t
		//	{
		//		return expr.newton_raphson(val);
		//	}).time<std::chrono::nanoseconds>(i);
		//
		//	std::printf("%.0f;%lld\n", i, time_newton_raphson.count());
		//}

		// TIME NEWTON-RAPHSON
		const auto[time_newton_raphson, result_newton_raphson] = timer(
			[&](const math_constant::my_precision_t val)
			-> math_constant::my_precision_t
		{
			return expr.newton_raphson(val);
		}).time<std::chrono::nanoseconds>(1.0);

		// TIME BISECTION
		const auto[time_bisection, result_bisection] = timer(
			[&](const std::pair<math_constant::my_precision_t, math_constant::my_precision_t> val)
			-> math_constant::my_precision_t
		{
			return expr.bisection(val);
		}).time<std::chrono::nanoseconds>(std::make_pair(1.0, 2.0));

		// PRINT
		std::printf(" [Bisection]      %.10f - Took %lld ns\n", result_bisection, time_bisection.count());
		std::printf(" [Newton-Raphson] %.10f - Took %lld ns\n", result_newton_raphson, time_newton_raphson.count());
	}

	static inline auto third()
		noexcept -> void
	{
		std::printf("Testing cbroot(x)\n");

		const auto expr = expression<test_case::three<math_constant::my_precision_t>>();

		// TIME BISECTION
		const auto[time_bisection, result_bisection] = timer(
			[&](const std::pair<math_constant::my_precision_t, math_constant::my_precision_t> val)
			-> math_constant::my_precision_t
		{
			return expr.bisection(val);
		}).time<std::chrono::nanoseconds>(std::make_pair(-1.0, 1.0));


		// PRINT
		std::printf(" [Bisection]      %.10f - Took %lld ns\n", result_bisection, time_bisection.count());
	}
};