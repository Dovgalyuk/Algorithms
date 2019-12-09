#include "String.hpp"

String::String()
{
	real = data_size = 0;
	data = new char[real + 1];
	data[data_size] = '\0';
}

String::String(const char* source)
{
	data_size = 0;
	while (source[data_size])
		data_size++;
	real = data_size;
	data = new char[real + 1];
	data[data_size] = '\0';
	for (size_t i = 0; i < data_size; i++)
		data[i] = source[i];
}

String::String(const std::string& source)
{
	real = data_size = source.length();
	data = new char[real + 1];
	data[data_size] = '\0';
	for (size_t i = 0; i < data_size; i++)
		data[i] = source[i];
}

String::String(const String& source)
{
	real = data_size = source.data_size;
	data = new char[real + 1];
	data[data_size] = '\0';
	for (size_t i = 0; i < data_size; i++)
		data[i] = source.data[i];
}

String::~String()
{
	delete[] data;
}

String String::operator+(const String& taget) const
{
	String temp;
	temp.resize(this->data_size + taget.data_size, ' ');
	for (size_t i = 0; i < this->data_size; i++)
		temp[i] = this->data[i];
	for (size_t i = 0; i < taget.data_size; i++)
		temp[i + this->data_size] = taget.data[i];
	return temp;
}

String& String::operator+=(const String& taget)
{
	char* temp;
	temp = new char[this->data_size + taget.data_size + 1];
	for (size_t i = 0; i < this->data_size; i++)
		temp[i] = this->data[i];
	for (size_t i = 0; i < taget.data_size; i++)
		temp[i + this->data_size] = taget.data[i];
	real = data_size = this->data_size + taget.data_size;
	temp[data_size] = '\0';
	delete[] data;
	data = temp;
	return (*this);
}

String& String::operator=(const String& taget)
{
	delete[] data;
	real = data_size = taget.data_size;
	data = new char[real + 1];
	data[data_size] = '\0';
	for (size_t i = 0; i < data_size; i++)
		data[i] = taget.data[i];
	return (*this);
}

bool String::operator==(const String& taget) const
{
	if (this == &taget)
		return true;
	if (this->data_size != taget.data_size)
		return false;
	for (size_t i = 0; i < this->data_size; i++)
		if (this->data[i] != taget.data[i])
			return false;
	return true;
}

bool String::operator!=(const String& taget) const
{
	return !(*this == taget);
}

bool String::operator>(const String& taget) const
{
	size_t i = 0;
	while (data[i] && data[i] == taget.data[i])
		i++;
	return data[i] > taget.data[i];
}

bool String::operator<(const String& taget) const
{
	size_t i = 0;
	while (data[i] && data[i] == taget.data[i])
		i++;
	return data[i] < taget.data[i];
}

char& String::operator[](size_t index)
{
	return data[index];
}

const char& String::operator[](size_t index) const
{
	return data[index];
}

size_t String::length() const
{
	return data_size;
}

bool String::resize(size_t new_size, const char data)
{
	if (new_size < real)
	{
		this->data[new_size] = '\0';
		for (size_t i = data_size; i < new_size; i++)
			this->data[i] = data;
		data_size = new_size;
		return true;
	}
	char* temp;
	temp = new char[new_size + 1];
	if (!temp[0])
		return false;
	for (size_t i = 0; i < data_size; i++)
		temp[i] = this->data[i];
	for (size_t i = data_size; i < new_size; i++)
		temp[i] = data;
	temp[new_size] = '\0';
	delete[] this->data;
	real = data_size = new_size;
	this->data = temp;
	return true;
}

const char* String::c_type() const
{
	return data;
}

std::string String::std_type() const
{
	return std::string(this->data);
}

size_t String::find(const String& P) const
{
	String temp(P + String("#") + *this);
	Vector<size_t> prefix(temp.length(), 0);
	for (size_t i = 1; i < temp.length(); i++)
	{
		size_t k = prefix[i - 1];
		while (k > 0 && temp[i] != temp[k])
			k = prefix[k - 1];
		if (temp[i] == temp[k])
			k++;
		prefix[i] = k;
	}
	for (size_t i = 0; i < data_size; i++)
		if (prefix[P.data_size + i + 1] == P.data_size)
			return (i - P.data_size + 1);
	return -1;
}