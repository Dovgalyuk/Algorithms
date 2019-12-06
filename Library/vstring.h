#ifndef STRING_H
#define STRING_H
#include <string>
class vstring
{
public:
	vstring();
	vstring(const char* source);
	vstring(const std::string& source);
	vstring(const vstring& source);
	~vstring();
	vstring operator+(const vstring& taget);
	vstring& operator+=(const vstring& taget);
	bool operator==(const vstring& taget);
	bool operator!=(const vstring& taget);
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