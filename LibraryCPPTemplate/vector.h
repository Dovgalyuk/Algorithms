#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <algorithm>

template <typename Data>
class Vector
{
public:
    Vector()  
    {
        vector_size = 0;  
        max_size = 1;  
        data = new Data[max_size]; 
    }
    // copy constructor
    Vector(const Vector &a)
    {
        data = new Data[a.max_size];
        vector_size = a.vector_size;
        max_size = a.max_size;
        for (size_t i = 0; i < vector_size; i++) {
            data[i] = a.data[i];
        }
    }
    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this != &a) {
            delete[] data;
            vector_size = a.vector_size;
            max_size = a.max_size;
            data = new Data[max_size];

            for (size_t i = 0; i < vector_size; i++) {
                data[i] = a.data[i];
            }
        }
        return *this;
    } 
    
    void swap(Vector& other)
    {
        // используйте std::swap для обмена указателями на данные, размерами и максимальными размерами
        std::swap(data, other.data);
        std::swap(vector_size, other.vector_size);
        std::swap(max_size, other.max_size);
    }

    ~Vector()  
    {
        delete[] data;  
    }

    Data* get(size_t index) const {
    if (index < vector_size)
        return &data[index];
    else
        throw std::out_of_range("Index out of range");
}

    void set(size_t index, Data value)  
    {
        if (index < vector_size)  
            data[index] = value;  
        else
            throw std::out_of_range("Index out of range");  
    }

    void set(size_t index, std::nullptr_t)  
        {
            if constexpr (std::is_pointer<Data>::value) {
                // Если Data - указатель, просто присвоим nullptr
                if (index < vector_size)
                    data[index] = nullptr;
                else
                    throw std::out_of_range("Index out of range");
            } else {
                // В противном случае вызываем конструктор по умолчанию (предполагая, что Data имеет конструктор по умолчанию)
                if (index < vector_size)
                    data[index] = Data();
                else
                    throw std::out_of_range("Index out of range");
            }
        }

    size_t size() const  
    {
        return vector_size;
    }

    void resize(size_t size)  
    {
        if (size <= max_size)  
        {
            vector_size = size;  
            return;
        }

        size_t _max_size = size * 2;  
        Data* new_data = new Data[_max_size];  

        for (size_t i = 0; i < vector_size; i++)  
        {
            new_data[i] = data[i];
        }

        delete[] data;  
        data = new_data;  
        max_size = _max_size;  
        vector_size = size;  
    }

private:
    Data* data;  
    size_t vector_size;  
    size_t max_size;  
};


#endif