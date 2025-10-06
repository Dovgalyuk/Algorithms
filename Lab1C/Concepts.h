#pragma once
#include <concepts>

namespace cl::concepts {
	template<class T>
	concept comparableType = requires(T a, T b) {
		{ a == b } -> std::convertible_to<bool>;
		{ a > b } -> std::convertible_to<bool>;
		{ a < b } -> std::convertible_to<bool>;
	};

	template<class T>
	concept primitiveType = std::is_fundamental_v<T>;

	template<class T>
	concept summable = requires(T a, T b) {
		{ a + b } -> std::convertible_to<T>;
	};
}