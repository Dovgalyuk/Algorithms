#include "vstring.h"

vstring::vstring()
{
	data_size = 0;
	data = new char[data_size + 1];
	data[data_size] = '\0';
}

vstring::vstring(const char* source)
{
	data_size = 0;
	while (source[data_size])
		data_size++;
	data = new char[data_size + 1];
	data[data_size] = '\0';
	for (size_t i = 0; i < data_size; i++)
		data[i] = source[i];
}

vstring::vstring(const std::string& source)
{
	data_size = source.length();
	data = new char[data_size + 1];
	data[data_size] = '\0';
	for (size_t i = 0; i < data_size; i++)
		data[i] = source[i];
}

vstring::vstring(const vstring& source)
{
	data_size = source.data_size;
	data = new char[data_size + 1];
	data[data_size] = '\0';
	for (size_t i = 0; i < data_size; i++)
		data[i] = source.data[i];
}

vstring::~vstring()
{
	delete[] data;
}

vstring vstring::operator+(const vstring& taget)
{
	vstring temp;
	temp.resize(this->data_size + taget.data_size, ' ');
	for (size_t i = 0; i < this->data_size; i++)
		temp[i] = this->data[i];
	for (size_t i = 0; i < taget.data_size; i++)
		temp[i + this->data_size] = taget.data[i];
	return temp;
}

vstring& vstring::operator+=(const vstring& taget)
{
	char* temp;
	temp = new char[this->data_size + taget.data_size + 1];
	for (size_t i = 0; i < this->data_size; i++)
		temp[i] = this->data[i];
	for (size_t i = 0; i < taget.data_size; i++)
		temp[i + this->data_size] = taget.data[i];
	data_size = this->data_size + taget.data_size;
	temp[data_size] = '\0';
	delete[] data;
	data = temp;
	return (*this);
}

bool vstring::operator==(const vstring& taget)
{
	if (this == &taget)
		return true;
	if (this->data_size == taget.data_size)
		return false;
	for (size_t i = 0; i < this->data_size; i++)
		if (this->data[i] != taget.data[i])
			return false;
	return true;
}

bool vstring::operator!=(const vstring& taget)
{
	return !(*this == taget);
}

char& vstring::operator[](size_t index)
{
	return data[index];
}

size_t vstring::length()
{
	return data_size;
}

bool vstring::resize(size_t new_size, const char data)
{
	char* temp;
	temp = new char[new_size + 1];
	if (!temp[0])
		return false;
	for (size_t i = 0; i < (new_size < data_size ? new_size : data_size); i++)
		temp[i] = this->data[i];
	for (size_t i = new_size < data_size ? new_size : data_size; i < new_size; i++)
		temp[i] = data;
	temp[new_size] = '\0';
	delete[] this->data;
	data_size = new_size;
	this->data = temp;
	return true;
}

const char* vstring::c_type()
{
	return data;
}

std::string vstring::std_type()
{
	return std::string(this->data);
}