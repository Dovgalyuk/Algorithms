#include "string_slice.h"

#include <stdexcept>

StringSlice::StringSlice() noexcept : data_(emptyData()), size_(0)
{
}

StringSlice::StringSlice(const char* text) : data_(text == nullptr ? emptyData() : text), size_(lengthOf(text))
{
}

StringSlice::StringSlice(const char* text, std::size_t length) : data_(text == nullptr ? emptyData() : text), size_(length)
{
	if (text == nullptr && length != 0) {
		throw std::invalid_argument("Null source with non-zero length");
	}
}

StringSlice::StringSlice(const String& source, std::size_t position, std::size_t count) : data_(nullptr), size_(0)
{
	if (position > source.size()) {
		throw std::out_of_range("String slice position is out of range");
	}
	const std::size_t available = source.size() - position;
	size_ = count < available ? count : available;
	data_ = source.data() + position;
}

std::size_t StringSlice::size() const noexcept
{
	return size_;
}

std::size_t StringSlice::length() const noexcept
{
	return size_;
}

bool StringSlice::empty() const noexcept
{
	return size_ == 0;
}

const char* StringSlice::data() const noexcept
{
	return data_;
}

const char* StringSlice::c_str() const noexcept
{
	return data_;
}

const char& StringSlice::operator[](std::size_t index) const noexcept
{
	return data_[index];
}

const char& StringSlice::at(std::size_t index) const
{
	if (index >= size_) {
		throw std::out_of_range("String slice index is out of range");
	}
	return data_[index];
}

String StringSlice::copy() const
{
	return String(data_, size_);
}

StringSlice StringSlice::substr(std::size_t position, std::size_t count) const
{
	if (position > size_) {
		throw std::out_of_range("String slice position is out of range");
	}
	const std::size_t available = size_ - position;
	const std::size_t resultLength = count < available ? count : available;
	return StringSlice(data_ + position, resultLength);
}

std::size_t StringSlice::find(const StringSlice& needle, std::size_t position) const noexcept
{
	if (position > size_) {
		return String::npos;
	}
	if (needle.size_ == 0) {
		return position;
	}
	if (needle.size_ > size_ - position) {
		return String::npos;
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
	return String::npos;
}

int StringSlice::compare(const StringSlice& other) const noexcept
{
	const std::size_t commonLength = size_ < other.size_ ? size_ : other.size_;
	for (std::size_t i = 0; i < commonLength; i++)
	{
		const unsigned char left = static_cast<unsigned char>(data_[i]);
		const unsigned char right = static_cast<unsigned char>(other.data_[i]);
		if (left < right)
			return -1;
		if (left > right)
			return 1;
	}
	if (size_ < other.size_) {
		return -1;
	}
	if (size_ > other.size_) {
		return 1;
	}
	return 0;
}

StringSlice::operator String() const
{
	return copy();
}

String operator+(const StringSlice& left, const StringSlice& right)
{
	String result(left.data_, left.size_);
	result.append(right.data_, right.size_);
	return result;
}

String operator+(const String& left, const StringSlice& right)
{
	String result(left);
	result.append(right.data_, right.size_);
	return result;
}

String operator+(const StringSlice& left, const String& right)
{
	String result(left.data_, left.size_);
	result.append(right);
	return result;
}

String operator+(const StringSlice& left, const char* right)
{
	String result(left.data_, left.size_);
	result += String(right);
	return result;
}

String operator+(const char* left, const StringSlice& right)
{
	String result(left);
	result.append(right.data_, right.size_);
	return result;
}

bool operator==(const StringSlice& left, const StringSlice& right) noexcept
{
	return left.compare(right) == 0;
}

bool operator!=(const StringSlice& left, const StringSlice& right) noexcept
{
	return !(left == right);
}

bool operator<(const StringSlice& left, const StringSlice& right) noexcept
{
	return left.compare(right) < 0;
}

bool operator<=(const StringSlice& left, const StringSlice& right) noexcept
{
	return left.compare(right) <= 0;
}

bool operator>(const StringSlice& left, const StringSlice& right) noexcept
{
	return left.compare(right) > 0;
}

bool operator>=(const StringSlice& left, const StringSlice& right) noexcept
{
	return left.compare(right) >= 0;
}

bool operator==(const StringSlice& left, const String& right) noexcept
{
	return left.compare(StringSlice(right)) == 0;
}

bool operator==(const String& left, const StringSlice& right) noexcept
{
	return StringSlice(left).compare(right) == 0;
}

bool operator!=(const StringSlice& left, const String& right) noexcept
{
	return !(left == right);
}

bool operator!=(const String& left, const StringSlice& right) noexcept
{
	return !(left == right);
}

bool operator<(const StringSlice& left, const String& right) noexcept
{
	return left.compare(StringSlice(right)) < 0;
}

bool operator<(const String& left, const StringSlice& right) noexcept
{
	return StringSlice(left).compare(right) < 0;
}

bool operator<=(const StringSlice& left, const String& right) noexcept
{
	return left.compare(StringSlice(right)) <= 0;
}

bool operator<=(const String& left, const StringSlice& right) noexcept
{
	return StringSlice(left).compare(right) <= 0;
}

bool operator>(const StringSlice& left, const String& right) noexcept
{
	return left.compare(StringSlice(right)) > 0;
}

bool operator>(const String& left, const StringSlice& right) noexcept
{
	return StringSlice(left).compare(right) > 0;
}

bool operator>=(const StringSlice& left, const String& right) noexcept
{
	return left.compare(StringSlice(right)) >= 0;
}

bool operator>=(const String& left, const StringSlice& right) noexcept
{
	return StringSlice(left).compare(right) >= 0;
}

bool operator==(const StringSlice& left, const char* right)
{
	return left.compare(StringSlice(right)) == 0;
}

bool operator==(const char* left, const StringSlice& right)
{
	return StringSlice(left).compare(right) == 0;
}

bool operator!=(const StringSlice& left, const char* right)
{
	return !(left == right);
}

bool operator!=(const char* left, const StringSlice& right)
{
	return !(left == right);
}

bool operator<(const StringSlice& left, const char* right)
{
	return left.compare(StringSlice(right)) < 0;
}

bool operator<(const char* left, const StringSlice& right)
{
	return StringSlice(left).compare(right) < 0;
}

bool operator<=(const StringSlice& left, const char* right)
{
	return left.compare(StringSlice(right)) <= 0;
}

bool operator<=(const char* left, const StringSlice& right)
{
	return StringSlice(left).compare(right) <= 0;
}

bool operator>(const StringSlice& left, const char* right)
{
	return left.compare(StringSlice(right)) > 0;
}

bool operator>(const char* left, const StringSlice& right)
{
	return StringSlice(left).compare(right) > 0;
}

bool operator>=(const StringSlice& left, const char* right)
{
	return left.compare(StringSlice(right)) >= 0;
}

bool operator>=(const char* left, const StringSlice& right)
{
	return StringSlice(left).compare(right) >= 0;
}

const char* StringSlice::emptyData() noexcept
{
	return "";
}

std::size_t StringSlice::lengthOf(const char* text) noexcept
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
