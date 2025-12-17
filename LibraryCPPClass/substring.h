#ifndef SUBSTRING_H
#define SUBSTRING_H

#include "MyString.h"
#include <cstddef>

class String;

class StringSlice
{
public:
    StringSlice(const String& source, std::size_t start, std::size_t length);

    std::size_t size() const;
    const char* data() const;
    const char* c_str() const;
    char operator[](std::size_t index) const;

    void print() const;

private:
    const String& source;
    std::size_t start;
    std::size_t length;
};

#endif
