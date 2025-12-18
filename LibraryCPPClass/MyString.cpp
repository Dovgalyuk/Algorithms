#include "MyString.h"

using namespace std;

String::String()
{
    size_ = 0;
    capacity_ = 1;
    data_ = new char[capacity_];
    data_[0] = '\0';
}

String::String(const String& a)
{
    size_ = a.size_;
    capacity_ = a.size_ + 1;
    data_ = new char[capacity_];

    for (size_t i = 0; i <= size_; ++i)
    {
        data_[i] = a.data_[i];
    }
}

String::String(const char* s)
{
    size_ = 0;
    while (s[size_] != '\0')
        ++size_;

    capacity_ = size_ + 1;
    data_ = new char[capacity_];

    for (std::size_t i = 0; i < size_; ++i)
        data_[i] = s[i];

    data_[size_] = '\0';
}

String::String(const StringSlice& sl)
{
    size_ = sl.size();

    capacity_ = size_ + 1;
    data_ = new char[capacity_];

    for (std::size_t i = 0; i < size_; ++i)
        data_[i] = sl[i];

    data_[size_] = '\0';
}

String::~String()
{
    delete[] data_;
}

String& String::operator+=(const String& other)
{
    size_t old_size = size_;

    resize(size_ + other.size_);

    for (size_t i = 0; i < other.size_; ++i)
    {
        data_[old_size + i] = other.data_[i];
    }

    return *this;
}

String String::operator+(const String& other) const
{
    String result(*this);
    result += other;
    return result;
}

String& String::operator=(const String& a)
{
    if (this == &a) {
        return *this;
    }

    delete[] data_;

    size_ = a.size_;
    capacity_ = size_ + 1;

    data_ = new char[capacity_];

    for (size_t i = 0; i < size_; ++i) {
        data_[i] = a.data_[i];
    }

    data_[size_] = '\0';

    return *this;
}

size_t String::find(const String& pattern, size_t pos) const
{
    if (pattern.size_ == 0)
        return (pos <= size_) ? pos : npos;

    if (pos > size_)
        return npos;

    const size_t n = size_;
    const size_t m = pattern.size_;

    if (m > n - pos)
        return npos;

    size_t* pi = new size_t[m];
    pi[0] = 0;

    for (size_t i = 1; i < m; ++i)
    {
        size_t j = pi[i - 1];

        while (j > 0 && pattern.data_[i] != pattern.data_[j])
            j = pi[j - 1];

        if (pattern.data_[i] == pattern.data_[j])
            j++;

        pi[i] = j;
    }

    size_t j = 0;

    for (size_t i = pos; i < n; ++i)
    {
        while (j > 0 && data_[i] != pattern.data_[j])
            j = pi[j - 1];

        if (data_[i] == pattern.data_[j])
            ++j;

        if (j == m)
        {
            size_t start = i - m + 1;
            delete[] pi;
            return start;
        }
    }

    delete[] pi;
    return npos;
}


int String::compare(const String& other) const
{
    size_t min_len = (size_ < other.size_) ? size_ : other.size_;

    for (size_t i = 0; i < min_len; ++i)
    {
        if (data_[i] < other.data_[i])
            return -1;
        if (data_[i] > other.data_[i])
            return 1;
    }

    if (size_ < other.size_)
        return -1;
    if (size_ > other.size_)
        return 1;

    return 0;
}

bool String::operator==(const String& other) const
{
    return compare(other) == 0;
}

bool String::operator!=(const String& other) const
{
    return compare(other) != 0;
}

bool String::operator<(const String& other) const
{
    return compare(other) < 0;
}

bool String::operator>(const String& other) const
{
    return compare(other) > 0;
}

char& String::operator[](std::size_t index)
{
    return data_[index];
}

char String::operator[](size_t index) const
{
    return data_[index];
}

void String::resize(size_t new_size)
{
    if (new_size == size_)
        return;

    if (new_size < size_)
    {
        size_ = new_size;
        data_[size_] = '\0';
        return;
    }

    if (new_size + 1 > capacity_)
    {
        size_t new_capacity = new_size + 1;
        char* new_data = new char[new_capacity];

        for (size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }

        delete[] data_;

        data_ = new_data;
        capacity_ = new_capacity;
    }

    for (size_t i = size_; i < new_size; ++i)
    {
        data_[i] = '\0';
    }

    size_ = new_size;
    data_[size_] = '\0';
}

const char* String::c_str() const
{
    return data_;
}

size_t String::size() const 
{ 
    return size_; 
}