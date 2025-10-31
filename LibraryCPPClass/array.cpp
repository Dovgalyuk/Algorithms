#include "array.h"

Array::Array(size_t size)
{
}

Array::Array(const Array &a)
{
}

Array &Array::operator=(const Array &a)
{
    return *this;
}

Array::~Array()
{
}

Data Array::get(size_t index) const
{
    return Data(0);
}

void Array::set(size_t index, Data value)
{
}

size_t Array::size() const
{
    return 0;
}
