#include "custom_string.h"

#include <cstdint>
#include <stdexcept>

String::String() : data_(new char[1]), size_(0), capacity_(0)
{
	data_[0] = '\0';
}

String::String(const char* text) : String(text, lengthOf(text))
{
}

String::String(const char* text, std::size_t length) : data_(nullptr), size_(length), capacity_(length)
{
	if (length == npos) {
		throw std::length_error("String length is too large");
	}
	if (text == nullptr && length != 0) {
		throw std::invalid_argument("Null source with non-zero length");
	}
	data_ = new char[length + 1];
	for (std::size_t i = 0; i < length; i++) {
		data_[i] = text[i];
	}
	data_[length] = '\0';
}

String::String(std::size_t count, char value) : data_(nullptr), size_(count), capacity_(count)
{
	if (count == npos) {
		throw std::length_error("String length is too large");
	}
	data_ = new char[count + 1];
	for (std::size_t i = 0; i < count; i++) {
		data_[i] = value;
	}
	data_[count] = '\0';
}

String::String(const String& other) : String(other.data_, other.size_)
{
}

String::~String()
{
	delete[] data_;
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		String temporary(other);
		swap(temporary);
	}
	return *this;
}

String& String::operator=(const char* text)
{
	String temporary(text);
	swap(temporary);
	return *this;
}

void String::swap(String& other) noexcept
{
	char* temporaryData = data_;
	data_ = other.data_;
	other.data_ = temporaryData;

	std::size_t temporarySize = size_;
	size_ = other.size_;
	other.size_ = temporarySize;

	std::size_t temporaryCapacity = capacity_;
	capacity_ = other.capacity_;
	other.capacity_ = temporaryCapacity;
}

std::size_t String::size() const noexcept
{
	return size_;
}

std::size_t String::length() const noexcept
{
	return size_;
}

std::size_t String::capacity() const noexcept
{
	return capacity_;
}

bool String::empty() const noexcept
{
	return size_ == 0;
}

const char* String::c_str() const noexcept
{
	return data_;
}

const char* String::data() const noexcept
{
	return data_;
}

char* String::data() noexcept
{
	return data_;
}

char& String::operator[](std::size_t index) noexcept
{
	return data_[index];
}

const char& String::operator[](std::size_t index) const noexcept
{
	return data_[index];
}

char& String::at(std::size_t index)
{
	if (index >= size_)
		throw std::out_of_range("String index is out of range");
	return data_[index];
}

const char& String::at(std::size_t index) const
{
	if (index >= size_)
		throw std::out_of_range("String index is out of range");
	return data_[index];
}

void String::reserve(std::size_t requestedCapacity)
{
	if (requestedCapacity <= capacity_) {
		return;
	}
	if (requestedCapacity == npos) {
		throw std::length_error("String capacity is too large");
	}
	std::size_t newCapacity = capacity_ == 0 ? 1 : capacity_;
	while (newCapacity < requestedCapacity)
	{
		if (newCapacity > (npos - 1) / 2)
		{
			newCapacity = requestedCapacity;
			break;
		}
		newCapacity *= 2;
	}

	char* newData = new char[newCapacity + 1];
	for (std::size_t i = 0; i < size_; i++) {
		newData[i] = data_[i];
	}
	newData[size_] = '\0';
	delete[] data_;
	data_ = newData;
	capacity_ = newCapacity;
}

void String::resize(std::size_t newSize, char value)
{
	if (newSize > capacity_) {
		reserve(newSize);
	}
	if (newSize > size_)
	{
		for (std::size_t i = size_; i < newSize; i++)
			data_[i] = value;
	}
	size_ = newSize;
	data_[size_] = '\0';
}

void String::clear() noexcept
{
	size_ = 0;
	data_[0] = '\0';
}

void String::append(const char* text, std::size_t count)
{
	if (count == 0) {
		return;
	}
	if (text == nullptr) {
		throw std::invalid_argument("Null source with non-zero length");
	}
	if (count > npos - size_) {
		throw std::length_error("String length is too large");
	}

	const std::uintptr_t sourceAddress = reinterpret_cast<std::uintptr_t>(text);
	const std::uintptr_t dataAddress = reinterpret_cast<std::uintptr_t>(data_);
	const bool aliases = sourceAddress >= dataAddress && sourceAddress <= dataAddress + size_;
	std::size_t sourceOffset = 0;
	if (aliases)
	{
		sourceOffset = static_cast<std::size_t>(sourceAddress - dataAddress);
		if (sourceOffset > size_ || count > size_ - sourceOffset)
			throw std::out_of_range("Append source range is out of bounds");
	}

	const std::size_t oldSize = size_;
	reserve(size_ + count);
	if (aliases) {
		text = data_ + sourceOffset;
	}
	for (std::size_t i = 0; i < count; i++) {
		data_[oldSize + i] = text[i];
	}
	size_ += count;
	data_[size_] = '\0';
}

void String::append(const String& other)
{
	append(other.data_, other.size_);
}

void String::append(char value)
{
	append(&value, 1);
}

String& String::operator+=(const String& other)
{
	append(other);
	return *this;
}

String& String::operator+=(char value)
{
	append(value);
	return *this;
}

String String::copy() const
{
	return String(data_, size_);
}

String String::substr(std::size_t position, std::size_t count) const
{
	if (position > size_) {
		throw std::out_of_range("String substring position is out of range");
	}
	const std::size_t available = size_ - position;
	const std::size_t resultLength = count < available ? count : available;
	return String(data_ + position, resultLength);
}

std::size_t String::find(const String& needle, std::size_t position) const noexcept
{
	if (position > size_) {
		return npos;
	}
	if (needle.size_ == 0) {
		return position;
	}
	if (needle.size_ > size_ - position) {
		return npos;
	}

	const std::size_t lastStart = size_ - needle.size_;
	for (std::size_t i = position; i <= lastStart; i++)
	{
		std::size_t j = 0;
		while (j < needle.size_ && data_[i + j] == needle.data_[j])
			j++;
		if (j == needle.size_)
			return i;
	}
	return npos;
}

int String::compare(const String& other) const noexcept
{
	const std::size_t commonLength = size_ < other.size_ ? size_ : other.size_;
	for (std::size_t i = 0; i < commonLength; i++)
	{
		const unsigned char left = static_cast<unsigned char>(data_[i]);
		const unsigned char right = static_cast<unsigned char>(other.data_[i]);
		if (left < right) {
			return -1;
		}
		if (left > right) {
			return 1;
		}
	}
	if (size_ < other.size_) {
		return -1;
	}
	if (size_ > other.size_) {
		return 1;
	}
	return 0;
}

String operator+(const String& left, const String& right)
{
	String result(left);
	result.append(right);
	return result;
}

bool operator==(const String& left, const String& right) noexcept
{
	return left.compare(right) == 0;
}

bool operator!=(const String& left, const String& right) noexcept
{
	return !(left == right);
}

bool operator<(const String& left, const String& right) noexcept
{
	return left.compare(right) < 0;
}

bool operator<=(const String& left, const String& right) noexcept
{
	return left.compare(right) <= 0;
}

bool operator>(const String& left, const String& right) noexcept
{
	return left.compare(right) > 0;
}

bool operator>=(const String& left, const String& right) noexcept
{
	return left.compare(right) >= 0;
}

namespace
{
	int compareStringToCString(const String& left, const char* right) noexcept
	{
		if (right == nullptr) {
			right = "";
		}

		std::size_t rightSize = 0;
		while (right[rightSize] != '\0') {
			rightSize++;
		}

		const std::size_t commonSize = left.size() < rightSize ? left.size() : rightSize;
		const char* leftData = left.data();

		for (std::size_t i = 0; i < commonSize; i++)
		{
			const unsigned char leftChar = static_cast<unsigned char>(leftData[i]);
			const unsigned char rightChar = static_cast<unsigned char>(right[i]);
			if (leftChar < rightChar)
				return -1;
			if (leftChar > rightChar)
				return 1;
		}

		if (left.size() < rightSize) {
			return -1;
		}
		if (left.size() > rightSize) {
			return 1;
		}
		return 0;
	}
}

bool operator==(const String& left, const char* right) noexcept
{
	return compareStringToCString(left, right) == 0;
}

bool operator==(const char* left, const String& right) noexcept
{
	return compareStringToCString(right, left) == 0;
}

bool operator!=(const String& left, const char* right) noexcept
{
	return !(left == right);
}

bool operator!=(const char* left, const String& right) noexcept
{
	return !(left == right);
}

bool operator<(const String& left, const char* right) noexcept
{
	return compareStringToCString(left, right) < 0;
}

bool operator<(const char* left, const String& right) noexcept
{
	return compareStringToCString(right, left) > 0;
}

bool operator<=(const String& left, const char* right) noexcept
{
	return compareStringToCString(left, right) <= 0;
}

bool operator<=(const char* left, const String& right) noexcept
{
	return compareStringToCString(right, left) >= 0;
}

bool operator>(const String& left, const char* right) noexcept
{
	return compareStringToCString(left, right) > 0;
}

bool operator>(const char* left, const String& right) noexcept
{
	return compareStringToCString(right, left) < 0;
}

bool operator>=(const String& left, const char* right) noexcept
{
	return compareStringToCString(left, right) >= 0;
}

bool operator>=(const char* left, const String& right) noexcept
{
	return compareStringToCString(right, left) <= 0;
}

std::size_t String::lengthOf(const char* text) noexcept
{
	if (text == nullptr) {
		return 0;
	}
	std::size_t length = 0;
	while (text[length] != '\0') {
		length++;
	}
	return length;
}
