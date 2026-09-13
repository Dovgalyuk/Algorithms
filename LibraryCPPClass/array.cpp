#include "array.h"

Array::Array(size_t size)
{
    array_size = size;
    elements = new Data[size];
}

Array::Array(const Array &a)
{
    array_size = a.array_size;
    elements = new Data[array_size];
    for (size_t index = 0; index < array_size; index++) {
        elements[index] = a.elements[index];
    }
}

Array &Array::operator=(const Array &a)
{
    if (this == &a) {
        return *this;
    }
    delete [] elements;
    array_size = a.array_size;
    elements = new Data[array_size];
    for (size_t i = 0;i<array_size;i++) {
        elements[i] = a.elements[i];
    }
    return *this;

}

Array::~Array()
{
    delete [] elements;
}

Data Array::get(size_t index) const
{
    if (index < array_size) {
        return elements[index];
    }
    return Data(0);
}

void Array::set(size_t index, Data value)
{
    if (index < array_size) {
        elements[index] = value;
    }
}

size_t Array::size() const
{
    return array_size;
}
