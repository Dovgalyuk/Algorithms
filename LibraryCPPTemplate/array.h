#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename T> class Array
{
public:
    // create array
    explicit Array(size_t size) : m_size(size), m_data(new T[size])
    {
    }

    // copy constructor
    Array(const Array &a) : m_size(a.m_size), m_data(new T[a.m_size])
    {
        for (size_t i = 0; i < m_size; ++i)
            m_data[i] = a.m_data[i];
    }

    // assignment operator
    Array &operator=(const Array &a)
    {
        if (this != &a)
        {
            delete[] m_data;

            m_size = a.m_size;
            m_data = new T[m_size];
            for (size_t i = 0; i < m_size; ++i)
                m_data[i] = a.m_data[i];
        }
        return *this;
    }

    // delete array, free memory
    ~Array()
    {
        delete[] m_data;
    }

    // returns specified array element
    T get(size_t index) const
    {
        if (index >= m_size)
            throw std::out_of_range("Выход за пределы массива");
        return m_data[index];
    }

    // sets the specified array element to the value
    void set(size_t index, T value)
    {
        if (index >= m_size)
            throw std::out_of_range("Выход за пределы массива");
        m_data[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return m_size;
    }

private:
    // private T should be here
    size_t m_size; 
    T *m_data;  
};

#endif
