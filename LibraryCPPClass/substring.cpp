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

void StringSlice::print() const
{
    for (size_t i = 0; i < length; ++i) {
        cout << (*this)[i];
    }
    cout << endl;
}
