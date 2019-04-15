#include "analysis.hpp"

#include <windows.h>

int main() noexcept
{
	// SET THREAD PRIORITY TO MAKE SURE NO OPERATIONS ARE DEFERRED
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	
	// CALCULATE DELTA VALUE
	analysis::override_precision();

	// RUN TEST CASES
	analysis::first();
	analysis::second();
	analysis::third();
	
	system("pause");

	// CALCULATE NEWTON RAPHSON SPEED
	//analysis::sample_newton_raphson();
}