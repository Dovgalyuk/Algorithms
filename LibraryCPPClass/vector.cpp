#include "vector.h"
#include <stdexcept>


using namespace std;

Vector::Vector() : elements(nullptr), volume(0), len(0){
}

Vector::Vector(const Vector &a) : volume(a.volume), len(a.len)
{
    copy(a);
}

void Vector::copy(const Vector &a) {
    elements = new Data[volume];
    for(size_t i = 0; i < len; i++)
        elements[i] = a.elements[i];
    
}

Vector &Vector::operator=(const Vector &a)
{
    if (this != &a) {
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

Data Vector::get(size_t index) const
{
    if (index < len)
        return elements[index];

    throw out_of_range("Index out of bounds");

}

void Vector::set(size_t index, Data value)
{
    if (index < len)
        elements[index] = value;
    else
        throw out_of_range("Index out of bounds");
}

size_t Vector::size() const
{
    return len;
}

void Vector::resize(size_t size)
{
    size_t exp_len;
    if (size > volume) {
        if (volume > 0)
            exp_len = volume;
        else
            exp_len = 1;

        while (exp_len < size)
            exp_len *= 2;

        Data* data = new Data[exp_len];

        for (size_t i = 0; i < len; i++)
            data[i] = elements[i];

        delete[] elements;
        elements = data;
        volume = exp_len;
    }
    len = size;

    
}

void Vector::push_back(Data value) {
    resize(len + 1);
    elements[len - 1] = value;
}
