#ifndef CUSTOM_STRING_SLICE_H
#define CUSTOM_STRING_SLICE_H

#include "custom_string.h"

#include <cstddef>

class StringSlice
{
public:
	StringSlice() noexcept;
	StringSlice(const char* text);
	StringSlice(const char* text, std::size_t length);
	StringSlice(const String& source, std::size_t position = 0, std::size_t count = String::npos);

	std::size_t size() const noexcept;
	std::size_t length() const noexcept;
	bool empty() const noexcept;

	const char* data() const noexcept;
	const char* c_str() const noexcept;

	const char& operator[](std::size_t index) const noexcept;
	const char& at(std::size_t index) const;

	String copy() const;
	StringSlice substr(std::size_t position, std::size_t count = String::npos) const;
	std::size_t find(const StringSlice& needle, std::size_t position = 0) const noexcept;
	int compare(const StringSlice& other) const noexcept;

	operator String() const;

	friend String operator+(const StringSlice& left, const StringSlice& right);
	friend String operator+(const String& left, const StringSlice& right);
	friend String operator+(const StringSlice& left, const String& right);
	friend String operator+(const StringSlice& left, const char* right);
	friend String operator+(const char* left, const StringSlice& right);

	friend bool operator==(const StringSlice& left, const StringSlice& right) noexcept;
	friend bool operator!=(const StringSlice& left, const StringSlice& right) noexcept;
	friend bool operator<(const StringSlice& left, const StringSlice& right) noexcept;
	friend bool operator<=(const StringSlice& left, const StringSlice& right) noexcept;
	friend bool operator>(const StringSlice& left, const StringSlice& right) noexcept;
	friend bool operator>=(const StringSlice& left, const StringSlice& right) noexcept;

	friend bool operator==(const StringSlice& left, const String& right) noexcept;
	friend bool operator==(const String& left, const StringSlice& right) noexcept;
	friend bool operator!=(const StringSlice& left, const String& right) noexcept;
	friend bool operator!=(const String& left, const StringSlice& right) noexcept;
	friend bool operator<(const StringSlice& left, const String& right) noexcept;
	friend bool operator<(const String& left, const StringSlice& right) noexcept;
	friend bool operator<=(const StringSlice& left, const String& right) noexcept;
	friend bool operator<=(const String& left, const StringSlice& right) noexcept;
	friend bool operator>(const StringSlice& left, const String& right) noexcept;
	friend bool operator>(const String& left, const StringSlice& right) noexcept;
	friend bool operator>=(const StringSlice& left, const String& right) noexcept;
	friend bool operator>=(const String& left, const StringSlice& right) noexcept;

	friend bool operator==(const StringSlice& left, const char* right);
	friend bool operator==(const char* left, const StringSlice& right);
	friend bool operator!=(const StringSlice& left, const char* right);
	friend bool operator!=(const char* left, const StringSlice& right);
	friend bool operator<(const StringSlice& left, const char* right);
	friend bool operator<(const char* left, const StringSlice& right);
	friend bool operator<=(const StringSlice& left, const char* right);
	friend bool operator<=(const char* left, const StringSlice& right);
	friend bool operator>(const StringSlice& left, const char* right);
	friend bool operator>(const char* left, const StringSlice& right);
	friend bool operator>=(const StringSlice& left, const char* right);
	friend bool operator>=(const char* left, const StringSlice& right);

private:
	static const char* emptyData() noexcept;
	static std::size_t lengthOf(const char* text) noexcept;

	const char* data_;
	std::size_t size_;
};

#endif
