#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data> class Array
{
public:
    // create array
    explicit Array(size_t size) : m_size(size), m_data(new Data[size]) {}

    // copy constructor
    Array(const Array<Data> &a)
    {
        m_size = a.m_size;
        m_data = new Data[m_size];
        for (size_t i = 0; i < m_size; i++) 
        {
            m_data[i] = a.m_data[i];
        }
    }

    // assignment operator
    Array &operator=(const Array<Data> &a)
    {
        if (this != &a)
        {
            delete[] m_data;
            m_size = a.m_size;
            m_data = new Data[m_size];
            for (size_t i = 0; i < m_size; i++)
            {
                m_data[i] = a.m_data[i];
            }
        }
        return *this;
    }

    // delete array, free memory
    ~Array()
    {
        delete[] m_data;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return m_data[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        m_data[index] = value;
    }

    size_t m_size;
    // returns array size
    size_t size() const
    {
        return this->m_size;
    }

private:
    Data* m_data;
};

#endif
