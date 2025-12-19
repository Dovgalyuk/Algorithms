#include "substring.h"
#include <iostream>

using namespace std;

StringSlice::StringSlice(const String& src, size_t str, size_t lng)
    : source(src), start(str), length(lng)
{
    if (str + lng > src.size()) {
        throw out_of_range("Slice out of bounds");
    }
}

StringSlice::operator String() const
{
    return String(*this);
}


size_t StringSlice::size() const
{
    return length;
}

const char* StringSlice::data() const
{
    return source.c_str() + start;
}

const char* StringSlice::c_str() const
{
    return data();
}

char StringSlice::operator[](size_t index) const
{
    if (index >= length) {
        throw out_of_range("Index out of range");
    }
    return source[start + index];
}

bool StringSlice::operator==(const StringSlice& other) const
{
    if (length != other.length)
        return false;

    for (size_t i = 0; i < length; ++i)
    {
        if ((*this)[i] != other[i])
            return false;
    }

    return true;
}


bool StringSlice::operator<(const StringSlice& other) const
{
    size_t min_len = (length < other.length) ? length : other.length;

    for (size_t i = 0; i < min_len; ++i)
    {
        if ((*this)[i] < other[i])
            return true;
        if ((*this)[i] > other[i])
            return false;
    }

    return length < other.length;
}


void StringSlice::print() const
{
    for (size_t i = 0; i < length; ++i) {
        cout << (*this)[i];
    }
    cout << endl;
}
