#include "analysis.hpp"

int main() noexcept
{
	analysis::first();
	analysis::second();
	analysis::third();

	// VALUE CHECK

	// ONE

	
	

	// TWO
	std::printf("Two\n");
	std::printf(" [Bisection]      %.10f\n", expression< test_case::two<my_precision_t> >().bisection(std::make_pair(1.0, 2.0)));
	std::printf(" [Newton-Raphson] %.10f\n", expression< test_case::two<my_precision_t> >().newton_raphson(1.0));
	
	// THREE
	std::printf("Three\n");
	std::printf(" [Bisection]      %.10f\n", expression< test_case::three<my_precision_t> >().bisection(std::make_pair(-1.0, 1.0)));

	// NOT SUPPORTED
	// std::printf(" [Newton-Raphson] %.10f\n",	expression< test_case::three<my_precision_t> >().newton_raphson(1.0));

	//const auto [val, result] = timer< test_case::one<my_precision_t> >().time<std::chrono::nanoseconds>(15.0);
	//std::cout << val.count() << std::endl;
	//std::cout << result << std::endl;
}