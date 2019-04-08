#pragma once
#include <iostream>
#include <array>

#include "expression.hpp"
#include "test_case.hpp"
#include "timer.hpp"
#include "math_constant.hpp"

class analysis
{
public:
	static inline auto guess_precision()
		noexcept -> math_constant::my_precision_t
	{
		std::printf("Guessing precision..\n");

		// SET UP BASE DELTA
		const auto expr = expression<test_case::two<math_constant::my_precision_t>>();
		constexpr auto value = math_constant::my_precision_t{12.345678};					// ARBITRARY
		constexpr auto real_derivative = math_constant::my_precision_t{456.247295839052};	// CALCULATED BY WOLFRAM-ALPHA

		// ESTIMATED GUESS FOR OPTIMAL DELTA VALUE
		const auto estimated_delta = std::sqrt(std::numeric_limits<math_constant::my_precision_t>::epsilon());

		// VARIABLE FOR OUR BRUTEFORCED, MORE PRECISE DELTA
		auto bruteforced_delta = estimated_delta;

		// MEASURE PRECISION TO COMPARE GUESSES
		auto min_precision = math_constant::my_precision_t{ 1.0 };

		// ITERATE FROM ESTIMATION +- DESIRED PRECISION
		constexpr auto desired_precision = math_constant::my_precision_t{0.0000001};
		for (auto i = -desired_precision;
				  i < desired_precision;
				  i += std::numeric_limits<math_constant::my_precision_t>::epsilon())
		{
			// CALCULATE DERIVATIVE FROM CURRENT, GUESSED DELTA
			const auto derivative = expr.derivative_2(value, estimated_delta + i);

			// CALCULATE PRECISION FOR COMPARISON
			const auto precision = std::abs(real_derivative - derivative);

			// IF DELTA YIELDS MORE PRECISE RESULTS THAN PREVIOUS, CACHE DELTA
			if (precision < min_precision)
			{
				min_precision = precision;
				bruteforced_delta = estimated_delta + i;
			}
		}
		
		// OUTPUT BRUTEFORCE RESULTS
		std::printf(" [Real]      %.12f\n", real_derivative);
		std::printf(" [Brute]     %.12f\n", expr.derivative_2(value, bruteforced_delta));
		std::printf(" [Precision] %.14f\n", min_precision);
		std::printf(" [Delta]     %.14f\n", bruteforced_delta);

		return bruteforced_delta;
	}

	static inline auto override_precision()
		noexcept -> void
	{
		math_constant::best_delta = analysis::guess_precision();
	}

	static inline auto sample_newton_raphson()
		noexcept -> void
	{
		std::printf("Sampling Newton-Raphson execution times..\n");

		const auto expr = expression<test_case::two<math_constant::my_precision_t>>();

		constexpr auto execution_interval = 1000;	// THIS DETERMINES THE MAXIMUM RANGE FOR THE SAMPLE LIST
		constexpr auto sample_count = 10000;		// AMOUNT OF SAMPLES

		// ARRAY OF EXECUTION TIMES
		auto samples = std::array<std::uint64_t, execution_interval>();

		// SUM EXECUTION TIMES
		for (size_t i = 0; i < sample_count; i++)
		{
			for (double guess = 1.0; guess < execution_interval; guess++)
			{
				// TIME NEWTON RAPHSON
				const auto[time_newton_raphson, result_newton_raphson] = timer(
					[&](const math_constant::my_precision_t val)
					-> math_constant::my_precision_t
				{
					return expr.newton_raphson(val);
				}).time<std::chrono::nanoseconds>(i);

				// ADD EXECUTION TIME TO LIST OF SAMPLES
				samples[guess] += time_newton_raphson.count();
			}
		}

		// PRINT RESULTS
		for (size_t i = 1; i < execution_interval; i++)
		{
			const auto average = samples[i] / sample_count;
			std::printf("%lld;%lld\n", i, average);
		}
	}

	// TEST CASES
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
		std::printf(" [Bisection]      %.14f - Took %lld ns\n", result_bisection, time_bisection.count());
		std::printf(" [Newton-Raphson] %.14f - Took %lld ns\n", result_newton_raphson, time_newton_raphson.count());
	}

	static inline auto second()
		noexcept -> void
	{
		std::printf("Testing x^3 - x - 2\n");

		const auto expr = expression<test_case::two<math_constant::my_precision_t>>();

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
		std::printf(" [Bisection]      %.14f - Took %lld ns\n", result_bisection, time_bisection.count());
		std::printf(" [Newton-Raphson] %.14f - Took %lld ns\n", result_newton_raphson, time_newton_raphson.count());
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
		std::printf(" [Bisection]      %.14f - Took %lld ns\n", result_bisection, time_bisection.count());
	}
};