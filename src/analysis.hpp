#pragma once
#include <iostream>
#include "expression.hpp"
#include "test_case.hpp"
#include "timer.hpp"

class analysis
{
	using my_precision_t = double;

public:
	static inline auto first()
		noexcept -> void
	{
		std::printf("First\n");

		const auto expr_1 = expression< test_case::one<my_precision_t> >();
		const auto clock = timer([&](const my_precision_t val) -> my_precision_t
		{
			return val;
		});

		const auto[a, b] = clock.time<std::chrono::nanoseconds>(15.0);

		std::printf("%lld - %f\n", a.count(), b);

		std::printf(" [Bisection]      %.10f\n", expr_1.bisection(std::make_pair(-1.0, 1.0)));
		std::printf(" [Newton-Raphson] %.10f\n", expr_1.newton_raphson(1.0));
	}
};