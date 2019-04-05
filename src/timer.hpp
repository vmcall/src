#pragma once
#include <chrono>

template <class Fn_t>
class timer
{
public:
	explicit timer(Fn_t expression) : m_expression(expression) {}

	template <class T, class ...U>
	auto time(const U... args) 
		const noexcept -> std::pair<T, std::invoke_result_t<Fn_t, U...>>
	{
		// GET MONOTONIC CLOCK TIME
		const auto start_time = std::chrono::steady_clock::now();

		// RUN FUNCTION
		const auto result = m_expression(args...);

		// GET MONOTONIC CLOCK TIME AGAIN
		const auto end_time = std::chrono::steady_clock::now();

		// RETURN THE TIME DELTA IN PREFERED, ARBITRARY TYPE
		return std::make_pair(
			std::chrono::duration_cast<T>(end_time - start_time),	// TIME DELTA
			result);												// EXPRESSION RESULT
	}
private:
	Fn_t m_expression;
};