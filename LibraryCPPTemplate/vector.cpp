#include <stdlib.h>
#include <iostream>
#include "vector.h"

Vector::Vector()
	:_size(0), _space(0) 
{
	_elem = new Data[_size];
}

Vector::~Vector()
{
	delete[] _elem;
}

//void Vector::Reserve(size_t size)
//{
//	//if (size < _space) return;
//	Data* p = new Data[size];
//	for (int i = 0; i < size; i++) 
//		p[i] = _elem[i];
//
//	_space *= 2;
//	delete _elem;
//	_elem = p;
//}

Data Vector::GetValue(size_t index) const
{
	return _elem[index];
}

void Vector::Set(size_t index, Data value)
{
	if (index > _size) Resize(index);
	_elem[index] = value;
}

size_t Vector::GetSize() const
{
	return _size;
}

void Vector::Resize(size_t size)
{
//	if (size > _size)
//	{
//		Reserve(size);
//		for (int i = _size; i < size; i++)
//			_elem[i] = Data();
//	}
//	_size = size;
    if (size < _size)
    {
        _size = size;
    }
    else {
        size_t newSize = size * 2;
        Data* newVector = new Data[newSize];
        for (int i = 0; i < _size; i++)
        {
            newVector[i] = _elem[i];
        }
        delete[] _elem;
        _elem = newVector;
        _size = size;
        _space = newSize;
    }
}

size_t Vector::GetCapacity() const
{
	return _space;
}