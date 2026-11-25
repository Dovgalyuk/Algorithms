#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H

#include <cstddef>

class String
{
public:
	static constexpr std::size_t npos = static_cast<std::size_t>(-1);

	String();
	String(const char* text);
	String(const char* text, std::size_t length);
	String(std::size_t count, char value);
	String(const String& other);
	~String();

	String& operator=(const String& other);
	String& operator=(const char* text);

	void swap(String& other) noexcept;

	std::size_t size() const noexcept;
	std::size_t length() const noexcept;
	std::size_t capacity() const noexcept;
	bool empty() const noexcept;

	const char* c_str() const noexcept;
	const char* data() const noexcept;
	char* data() noexcept;

	char& operator[](std::size_t index) noexcept;
	const char& operator[](std::size_t index) const noexcept;

	char& at(std::size_t index);
	const char& at(std::size_t index) const;

	void reserve(std::size_t requestedCapacity);
	void resize(std::size_t newSize, char value = '\0');
	void clear() noexcept;

	void append(const char* text, std::size_t count);
	void append(const String& other);
	void append(char value);

	String& operator+=(const String& other);
	String& operator+=(char value);

	String copy() const;
	String substr(std::size_t position, std::size_t count = npos) const;
	std::size_t find(const String& needle, std::size_t position = 0) const noexcept;
	int compare(const String& other) const noexcept;

	friend String operator+(const String& left, const String& right);
	friend bool operator==(const String& left, const String& right) noexcept;
	friend bool operator!=(const String& left, const String& right) noexcept;
	friend bool operator<(const String& left, const String& right) noexcept;
	friend bool operator<=(const String& left, const String& right) noexcept;
	friend bool operator>(const String& left, const String& right) noexcept;
	friend bool operator>=(const String& left, const String& right) noexcept;

	friend bool operator==(const String& left, const char* right) noexcept;
	friend bool operator==(const char* left, const String& right) noexcept;
	friend bool operator!=(const String& left, const char* right) noexcept;
	friend bool operator!=(const char* left, const String& right) noexcept;
	friend bool operator<(const String& left, const char* right) noexcept;
	friend bool operator<(const char* left, const String& right) noexcept;
	friend bool operator<=(const String& left, const char* right) noexcept;
	friend bool operator<=(const char* left, const String& right) noexcept;
	friend bool operator>(const String& left, const char* right) noexcept;
	friend bool operator>(const char* left, const String& right) noexcept;
	friend bool operator>=(const String& left, const char* right) noexcept;
	friend bool operator>=(const char* left, const String& right) noexcept;

private:
	static std::size_t lengthOf(const char* text) noexcept;

	char* data_;
	std::size_t size_;
	std::size_t capacity_;
};

#endif
