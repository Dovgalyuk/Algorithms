#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

#ifdef USE_STRING_DATA
#include <string>
typedef std::string Data;
#else
typedef int Data;
#endif

class Vector {
   public:
    Vector();
    Vector(const Vector& a);
    Vector& operator=(const Vector& a);
    ~Vector();

    const Data& get(size_t index) const;
    void set(size_t index, const Data& value);
    size_t size() const;
    void resize(size_t new_size);

   private:
    Data* data_;
    size_t size_;
    size_t capacity_;
};

#endif
