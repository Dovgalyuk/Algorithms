#pragma once
#include <iostream>
#include <functional>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include "array.h"
#include "concepts.h"

namespace cl {

	enum class MoveDirection {
		Right,
		Left
	};

	namespace algorithms {

		template<concepts::comparableType T, class Iterator>
		constexpr std::pair<std::size_t, std::size_t> findMinMaxIndex(Iterator begin, Iterator end) {
			//auto [minElement, maxElement] = std::minmax_element(array.begin(), array.end());

			if (begin == end) throw std::runtime_error("Empty range passed to findMinMaxIndex");
			
			std::size_t minElementIndex{ };
			std::size_t maxElementIndex{ };

			for (Iterator it = begin; it != end; ++it) {
				if (*(begin + minElementIndex) > *it) {
					minElementIndex = it - begin;
				}
				else if (*(begin + maxElementIndex) < *it) {
					maxElementIndex = it - begin;
				}
			}

			return { minElementIndex, maxElementIndex };
		}

		template<class T> constexpr auto getTypeCast() = delete;
		template<> constexpr auto getTypeCast<double>() { return [](auto s) { return std::stod(s); }; }
		template<> constexpr auto getTypeCast<float>() { return [](auto s) { return std::stof(s); }; }
		template<> constexpr auto getTypeCast<int>() { return [](auto s) { return std::stoi(s); }; }

		template<concepts::summable T, class Iterator>
		typename std::iterator_traits<Iterator>::value_type sum(Iterator begin, Iterator end) {
			// return std::accumulate(begin, end, value_type{});

			using value_type = typename std::iterator_traits<Iterator>::value_type;
			if (++begin == end) return value_type{};

			value_type result = value_type();

			for (; begin != end; ++begin) {
				result += *begin;
			}

			return result;
		}

		template<concepts::primitiveType T, class Iterator>
		void moveElements(Iterator begin, Iterator end, MoveDirection direction, int movePosition) {
			if (movePosition < 0) {
				throw std::invalid_argument("movePosition must be non-negative");
			}

			if (direction == MoveDirection::Right) {
				for (auto i = end - 1; i >= begin; --i) {
					if (i >= begin + movePosition) {
						*i = *(i - movePosition);
					}
					else {
						*i = T{ 0 };
					}
				}
			}

			else if (direction == MoveDirection::Left) {
				for (auto i = begin; i != end; ++i) {
					if (i <= end - 1 - movePosition) {
						*i = *(i + movePosition);
					}
					else {
						*i = T{ 0 };
					}
				}
			}
			else {
				throw std::runtime_error("Direction not found");
			}
		}

	}

	std::pair<MoveDirection, int> readDirectionFromFile(std::fstream& file) {
		std::string dirStr, stepStr;
		if (!(file >> dirStr >> stepStr)) {
			throw std::runtime_error("Failed to read direction and step from file");
		}

		MoveDirection direction;
		if (dirStr == "L") {
			direction = MoveDirection::Left;
		}
		else if (dirStr == "R") {
			direction = MoveDirection::Right;
		}
		else {
			throw std::runtime_error("Invalid direction: expected 'L' or 'R', got '" + dirStr + "'");
		}

		try {
			int moveStep = std::stoi(stepStr);
			if (moveStep < 0) {
				throw std::invalid_argument("Move step must be non-negative");
			}
			return { direction, moveStep };
		}
		catch (const std::exception&) {
			throw std::runtime_error("Invalid move step: " + stepStr);
		}
		
	}

	template<concepts::primitiveType T>
	Array<T> createArrayFromFile(std::fstream& file) {
		std::string sizeStr;
		if (!(file >> sizeStr)) {
			throw std::runtime_error("Failed to read array size");
		}

		std::size_t arraySize;
		
		try {
			arraySize = std::stoll(sizeStr);
		}
		catch (const std::exception&) {
			throw std::runtime_error("Failed to parse array size");
		}

		Array<T> resultArray(arraySize);

		std::string rawFileData;

		auto typeCast = algorithms::getTypeCast<T>();

		for (std::size_t index{}; index != arraySize && file >> rawFileData; ++index) {
			try {
				resultArray[index] = typeCast(rawFileData);
			}
			catch (const std::exception&) {
				throw std::runtime_error("Failed to parse element at index: " + std::to_string(index) + ": " + rawFileData);
			}
		}

		return resultArray;
	}	
}