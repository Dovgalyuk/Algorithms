#ifndef STRING_H
#define STRING_H
#include <string>
class String
{
public:
	String();
	String(const char* source);
	String(const std::string& source);
	String(const String& source);
	~String();
	String operator+(const String& taget);
	String& operator+=(const String& taget);
	bool operator==(const String& taget);
	bool operator!=(const String& taget);
	char& operator[](size_t index);
	size_t length();
	bool resize(size_t new_size, const char data);
	const char* c_type();
	std::string std_type();
private:
	char* data;
	size_t data_size;
};
#endif