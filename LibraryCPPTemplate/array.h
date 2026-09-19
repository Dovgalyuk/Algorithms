#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data> class Array
{
public:
    // create array
    explicit Array(size_t size)
    {
        size_=size;
        data_=new Data[size_];
    }

    // copy constructor
    Array(const Array &a)
    {
        size_=a.size_;
        data_=new Data[size_];
        for (size_t i=0;i<size_;i++) data_[i]= a.data_[i];
    }

    // assignment operator
    Array &operator=(const Array &a)
    {
        if (this != &a) {
            delete[] data_;
            size_ =a.size_;
            data_= new Data[size_];
            for (size_t i=0;i<size_;i++) data_[i]= a.data_[i];
        }
        return *this;
    }

    // delete array, free memory
    ~Array()
    {
        delete[] data_;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return data_[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        data_[index]=value;
    }

    // returns array size
    size_t size() const
    {
        return size_;
    }

private:
    // private data should be here
    Data* data_;
    size_t size_;
};

#endif
