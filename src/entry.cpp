#include <iostream>
#include "expression.hpp"

double test(double x)
{
	// x^3 - x - 2
	return std::pow(x, 3) - x - 2;
}

int main()
{
	const auto root = expression<test>().bisection(std::make_pair(1.0, 2.0));

	std::printf("Root: [%f]\n", root);
}