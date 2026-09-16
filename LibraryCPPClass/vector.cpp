#include "vector.h"

Vector::Vector() : elements(nullptr), volume(0), len(0)
{
}

Vector::Vector(const Vector &a) : volume(a.volume), len(a.len)
{
    copy(a);
}

Vector &Vector::operator=(const Vector &a)
{
    if (this != &a){
        delete[] elements;
        volume = a.volume;
        len = a.len;
        copy(a);
    }
    return *this;
}

Vector::~Vector()
{
    delete[] elements;
}

void Vector::copy(const Vector &a) {
    elements = new Data[volume];
    for (size_t i = 0; i< len; i++) {
        elements[i] = a.elements[i];
    }
}

Data Vector::get(size_t index) const
{
    if (index >= len){
        throw std::out_of_range("Vector::get: index out of range");
    }
    return elements[index];
}

void Vector::set(size_t index, Data value)
{
    if (index >= len) {
        throw std::out_of_range("Vector::set: index out of range");
    }
    elements[index] = value;
}

size_t Vector::size() const
{
    return len;
}

void Vector::resize(size_t size)
{
    if (size > volume) {
        size_t new_volume = (volume > 0) ? volume : 1;
        while (new_volume < size){
            new_volume *= 2;
        }

        Data* new_elements = new Data[new_volume];
        for (size_t i = 0; i < len; i++)
        {
            new_elements[i] = elements[i];
        }
        delete[] elements;
        elements = new_elements;
        volume = new_volume;
    }
    len = size;
}

void Vector::push_back(Data value)
{
    resize(len + 1);
    elements[len - 1] = value;
}

void Vector::reverse()
{
    // Меняем местами элементы симметрично от краёв к центру
    for (size_t i = 0; i < len / 2; i++) {
        Data tmp = elements[i];
        elements[i] = elements[len - 1 - i];
        elements[len - 1 - i] = tmp;
    }
}
