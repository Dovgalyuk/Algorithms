#pragma once
#include <cstddef>
#include <initializer_list>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "Iterator.h"

template<std::copyable T>
class StaticSizeArray {
public:
	StaticSizeArray() = delete;

	explicit StaticSizeArray(std::size_t arraySize) noexcept {
		data_ = new T[arraySize];
		size_ = arraySize;
	}

	StaticSizeArray(std::size_t arraySize, T defaultValue) noexcept : StaticSizeArray(arraySize) {
		for (std::size_t index = 0; index < size_; ++index) {
			data_[index] = defaultValue;
		}
	}

	StaticSizeArray(std::initializer_list<T> list) : StaticSizeArray(list.size()) {
		for (std::size_t index{}; auto& element : list) {
			data_[index++] = element;
		}
	}

	StaticSizeArray(const StaticSizeArray& other) : data_(nullptr), size_(0) {
		T* newData = new T[other.size_];
		size_ = other.size_;

		try {
			for (std::size_t index = 0; index < other.size_; ++index) {
				newData[index] = other[index];
			}
			data_ = newData;
		}
		catch (...) {
			delete[] newData;
			throw;
		}
	}

	StaticSizeArray(StaticSizeArray&& other) noexcept {
		data_ = other.data_;
		size_ = other.size_;

		other.data_ = nullptr;
	}
	
	~StaticSizeArray() noexcept {
		delete[] data_;
	}

	std::size_t size() const {
		return size_;
	}

	T& operator[](std::size_t index) {
		return data_[index];
	}

	const T& operator[](std::size_t index) const {
		return data_[index];
	}

	T& at(std::size_t index) {
		if (index >= size_) {
			throw std::out_of_range("StaticSizeArray::at: index out of range");
		}
		return data_[index];
	}

	const T& at(std::size_t index) const {
		if (index >= size_) {
			throw std::out_of_range("StaticSizeArray::at: index out of range");
		}
		return data_[index];
	}

	iterator<T> begin() noexcept {
		return iterator(data_);
	}

	iterator<T> end() noexcept {
		return iterator(data_ + size_);
	}

	iterator<const T> begin() const noexcept {
		return iterator<const T>(data_);
	}

	iterator<const T> end() const noexcept {
		return iterator<const T>(data_ + size_);
	}

	iterator<const T> cbegin() const noexcept {
		return iterator<const T>(data_);
	}

	iterator<const T> cend() const noexcept {
		return iterator<const T>(data_ + size_);
	}

private:
	T* data_;
	std::size_t size_;
};

template<class T>
std::ostream& operator<<(std::ostream& stream, const StaticSizeArray<T>& array) {
	stream << "(";
	for (std::size_t index{}; index < array.size(); ++index) {
		stream << std::to_string(array.at(index));
		if (index != (array.size() - 1)) stream << ", ";
	}
	return stream << ")";
}