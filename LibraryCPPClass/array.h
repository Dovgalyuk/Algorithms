#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <utility>

typedef int Data;

class Array {
   public:
    explicit Array(size_t size);
    Array(const Array& a);
    Array& operator=(const Array& a);
    ~Array();

    Data get(size_t index) const;
    void set(size_t index, Data value);

    size_t size() const;

   private:
    Data* data_;
    const size_t size_;
};

#endif
