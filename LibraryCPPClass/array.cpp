#include "array.h"

using namespace std;

Array::Array(size_t size) : arrSize(size), arrData(new Data[size]())
{
    for(size_t i = 0; i < m_size; i++) {
        arrData[i] = 0;
    }
}

Array::Array(const Array &a) : arrSize(a.arrSize), arrData(new Data[a.arrSize])
{
    for(size_t i = 0; i < arrSize; ++i){
        arrData[i] = a.arrData[i];
    }
}

Array &Array::operator=(const Array &a)
{
    if(this != &a){
        delete[] arrData;
        arrSize = a.arrSize;
        arrData = new Data[arrSize];
        for(size_t i = 0; i < arrSize; ++i){
            arrData[i] = a.arrData[i];
        }
    }
    return *this;
}

Array::~Array()
{
    delete[] arrData;
}

Data Array::get(size_t index) const
{
    if(index >= arrSize){
        throw out_of_range("Index out of bounds\n");
    }
    return arrData[index];
}

void Array::set(size_t index, Data value)
{
    if(index >= arrSize){
        throw out_of_range("Index out of bounds");
    }
    arrData[index] = value; 
}

size_t Array::size() const
{
    return arrSize;
}
