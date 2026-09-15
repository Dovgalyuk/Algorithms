#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
// Шаблонный динамический массив с проверкой границ и поддержкой копирования.
class arr {
private:
	std::size_t length;
	T* data;

public:
	// Выделяет память под заданное количество элементов.
	explicit arr(std::size_t size) : length(size), data(new T[size]) {}

	// Создаёт независимую копию другого массива вместе со всеми элементами.
	arr(const arr& other) : length(other.length), data(new T[other.length]) {
		for (std::size_t i = 0; i < length; ++i) {
			data[i] = other.data[i];
		}
	}

	// Освобождает память, выделенную для элементов массива.
	~arr() {
		delete[] data;
	}

	// Копирует элементы другого массива, если размеры массивов совпадают.
	arr& operator=(const arr& other) {
		if (this != &other) {
			if (length != other.length) {
				throw std::invalid_argument("Вышли за пределы диапазона");
			}
			for (std::size_t i = 0; i < length; ++i) {
				data[i] = other.data[i];
			}
		}
		return *this;
	}

	// Возвращает количество элементов в массиве.
	std::size_t size() const {
		return length;
	}

	// Возвращает изменяемый элемент по индексу после проверки границ.
	T& operator[](std::size_t index) {
		if (index >= length) {
			throw std::out_of_range("Массив вышел за пределы диапазона!");
		}
		return data[index];
	}

	// Возвращает неизменяемый элемент по индексу после проверки границ.
	const T& operator[](std::size_t index) const {
		if (index >= length) {
			throw std::out_of_range("Массив вышел за пределы диапазона!");
		}
		return data[index];
	}
};

#endif
