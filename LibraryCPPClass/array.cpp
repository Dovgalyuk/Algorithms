#include "array.h"

// «аглушка класса Array
Array::Array(size_t size) {
    (void)size; // убрать предупреждение
}

Array::Array(const Array& a) {
    (void)a;
}

Array& Array::operator=(const Array& a) {
    (void)a;
    return *this;
}

Array::~Array() {
}

Data Array::get(size_t index) const {
    (void)index;
    return Data(0);
}

void Array::set(size_t index, Data value) {
    (void)index;
    (void)value;
}

size_t Array::size() const {
    return 0;
}
