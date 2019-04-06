#include "analysis.hpp"

#include <windows.h>

int main() noexcept
{
	// SET THREAD PRIORITY TO MAKE SURE NO OPERATIONS ARE DEFERRED
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

	analysis::test_precision();
	
	analysis::first();
	analysis::second();
	analysis::third();
}