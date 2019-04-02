#include <iostream>
#include "expression.hpp"
#include "test_case.hpp"
#include "timer.hpp"

int main() noexcept
{
	using my_precision_t = double;

	std::printf("Deriative: [%f]\n",		expression< test_case::one<my_precision_t> >().deriative(0.0));
	std::printf("Bisection: [%f]\n",		expression< test_case::one<my_precision_t> >().bisection(std::make_pair(-1.0, 1.0)));
	std::printf("Newton Raphson: [%f]\n",	expression< test_case::two<my_precision_t> >().newton_raphson(5.0));


	for (size_t i = 0; i < 99; i++)
	{
		auto val = timer< test_case::one<my_precision_t> >().time<std::chrono::nanoseconds>(15.0);
		std::cout << val.count() << std::endl;
	}
	
}