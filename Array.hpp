#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
class arr {
private:
	std::size_t len;
	T* data;

public:
	explicit arr(std::size_t n) : len(n), data(new T[n]) {}

	arr(const arr& copy) : len(copy.len), data(new T[copy.len]) {
		for (std::size_t i = 0; i < len; ++i) {
			data[i] = copy.data[i];
		}
	}

	~arr() {
		delete[] data;
	}

	arr& operator=(const arr& copy) {
		if (this != &copy) {
			if (len != copy.len) {
				throw std::invalid_argument("Вышли за пределы диапазона");
			}
			for (std::size_t i = 0; i < len; ++i) {
				data[i] = copy.data[i];
			}
		}
		return *this;
	}

	std::size_t size() const {
		return len;
	}

	T& operator[](std::size_t i) {
		if (i >= len) {
			throw std::out_of_range("Массив вышел за пределы диапазона!");
		}
		return data[i];
	}

	const T& operator[](std::size_t i) const {
		if (i >= len) {
			throw std::out_of_range("Массив вышел за пределы диапазона!");
		}
		return data[i];
	}
};

#endif
