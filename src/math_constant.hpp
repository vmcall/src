#pragma once
#include <math.h>
#include <limits>

namespace math_constant
{
	using my_precision_t = double;
	static math_constant::my_precision_t best_delta = std::sqrt( std::numeric_limits<math_constant::my_precision_t>::epsilon() );
}