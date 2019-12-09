#ifndef STRING_H
#define STRING_H
#include <string>
#include "Vector.hpp"

class String
{
public:
	String();
	String(const char* source);
	String(const std::string& source);
	String(const String& source);
	~String();
	String operator+(const String& taget) const;
	String& operator+=(const String& taget);
	String& operator=(const String& taget);
	bool operator==(const String& taget)  const;
	bool operator!=(const String& taget) const;
	char& operator[](size_t index);
	size_t length() const;
	bool resize(size_t new_size, const char data);
	const char* c_type() const;
	std::string std_type() const;
	size_t find(const String& P) const;
private:
	char* data;
	size_t data_size;
};
#endif