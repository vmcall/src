#include <iostream>
#include "expression.hpp"

double test(double x) noexcept
{
	// x^3 - x - 2
	return std::pow(x, 3) - x - 2;
}

int main() noexcept
{
	std::printf("Deriative: [%f]\n", expression<test>().deriative(0.0));
	std::printf("Bisection: [%f]\n", expression<test>().bisection(std::make_pair(1.0, 2.0)));
	std::printf("Newton Raphson: [%f]\n", expression<test>().newton_raphson(5.0));
}