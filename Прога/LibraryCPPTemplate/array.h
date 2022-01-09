#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template<typename Data>
class Array {
private:
    // private data should be here
    Data *data_;
    size_t size_;

public:
    // create array
    Array(size_t size) {
        size_ = size;
        data_ = new Data(size_);
    }

    // delete array, free memory
    ~Array() {
        delete[] data_;
    }

    // returns specified array element
    Data get(size_t index) const {
        if(index < size_){
            return data_[index];
        }
        else{
            std::cout <<"ERROR";
            return 0;
        }
    }

    // sets the specified array element to the value
    void set(size_t index, Data value) {
        if (index < size_) {
            data_[index] = value;
        }
        std::cout <<"ERROR";
    }

    // returns array size
    size_t size() const {
        return size_;
    }
};


#endif
