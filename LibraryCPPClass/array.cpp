 #include "array.h"

Array::Array(size_t size)
{
    if (size > 0) {
        asize = size;
        adata = new Data[size];
    }
    else {
        adata = nullptr;
        asize = 0;
    }
}

Array::Array(const Array& a)
{
    size_t new_size = a.size();
    if (new_size > 0) {
        Data* new_data = new Data[new_size];
        for (size_t i = 0; i < new_size; ++i) {
            new_data[i] = a.get(i);
        }
        adata = new_data;
        asize = new_size;
    }
    else {
        adata = nullptr;
        asize = 0;
    }
}

Array& Array::operator=(const Array& a)
{
    if (this != &a) {
        size_t new_size = a.size();

        if (new_size > 0) {
            Data* new_data = new Data[new_size];
            for (size_t i = 0; i < new_size; ++i) {
                new_data[i] = a.get(i);
            }
            delete[] adata;
            adata = new_data;
            asize = new_size;
        }
    }
    return *this;
}

Array::~Array()
{
    delete[] adata;
}

Data Array::get(size_t index) const
{
    if (index < asize) {
        return adata[index];
    }
    else {
        return -1;
    }
}

void Array::set(size_t index, Data value)
{
    if (index < asize) {
        adata[index] = value;
    }
}

size_t Array::size() const
{
    return asize;
}