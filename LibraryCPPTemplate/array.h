#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

#include <cstddef>
#include <initializer_list>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <ranges>
#include "concepts.h"
#include "iterator.h"

template<std::copyable T>
class Array {
public:
	Array() = delete;

	explicit Array(std::size_t arraySize) {
		data_ = new T[arraySize];
		size_ = arraySize;
	}

	Array(std::size_t arraySize, T defaultValue) : Array(arraySize) {
		for (std::size_t index = 0; index < size_; ++index) {
			data_[index] = defaultValue;
		}
	}

	Array(std::initializer_list<T> list) : Array(list.size()) {
		for (std::size_t index{}; auto& element : list) {
			data_[index++] = element;
		}
	}

	Array(const Array& other) : data_(nullptr), size_(0) {
		T* newData = new T[other.size_];
		size_ = other.size_;

		try {
			for (std::size_t index{}; index < other.size_; ++index) {
				newData[index] = other[index];
			}
			data_ = newData;
		}
		catch (...) {
			delete[] newData;
			throw;
		}
	}

	Array(Array&& other) noexcept {
		data_ = other.data_;
		size_ = other.size_;

		other.data_ = nullptr;
	}

	Array& operator=(const Array& other) {
		if (&other != this) {
			delete[] data_;

			size_ = other.size_;
			data_ = new T[other.size_];

			for (std::size_t index{}; index < other.size_; ++index) {
				data_[index] = other[index];
			}
		}

		return *this;
	}

	Array& operator=(Array&& other) {
		if (&other != this) {
			delete[] data_;

			data_ = other.data_;
			size_ = other.size_;

			other.data_ = nullptr;
			other.size_ = 0;
		}

		return *this;
	}

	~Array() noexcept {
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
			throw std::out_of_range("Array::at: index out of range");
		}
		return data_[index];
	}

	const T& at(std::size_t index) const {
		if (index >= size_) {
			throw std::out_of_range("Array::at: index out of range");
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

	// function alias for array test

	T get(size_t index) const
	{
		return this->at(index);
	}

	void set(size_t index, T value)
	{
		this->at(index) = value;
	}

private:
	T* data_;
	std::size_t size_;
};

template<class T>
std::ostream& operator<<(std::ostream& stream, const Array<T>& array) {
	stream << "(";
	for (std::size_t index{}; index < array.size(); ++index) {
		stream << std::to_string(array.at(index));
		if (index != (array.size() - 1)) stream << ", ";
	}
	return stream << ")";
}

#endif
