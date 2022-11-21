#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

using std::ostream;
using std::endl;

template <typename Data> class Array
{
public:
    // create array
    explicit Array(size_t size): _size(size), _array(new Data[size]){}

    // assignment operator
    Array &operator=(const Array &a)
    {
        _size = a._size;
        _array = std::copy(a._array);
        return *this;
    }

    // delete array, free memory
    ~Array()
    {
        delete[] _array;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return _array[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        _array[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return _size;
    }

    friend ostream& operator<<(ostream& os, const Array<Data>& dt)
    {
        os << '[';
        for (int i = 0; i < dt._size; ++i) {
            os << dt.get(i);
            if (i + 1 != dt._size) {
                os << ',';
            }
        }
        os << ']' << endl;
        return os;
    }

    friend ostream& operator<<(ostream& os, const Array<Data>* dt)
    {
        os << '[';
        for (int i = 0; i < dt->_size; ++i) {
            os << dt->get(i);
            if (i + 1 != dt->_size) {
                os << ',';
            }
        }
        os << ']' << endl;
        return os;
    }

private:
    Data* _array;
    size_t _size;
    // private data should be here
};

#endif
