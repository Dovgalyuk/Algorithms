#include "apfel.h"

Array* read_array(istream& stream) {
    long long signed_size;
    if (!(stream >> signed_size) || signed_size <= 0) {
        return nullptr;
    }

    size_t size = static_cast<size_t>(signed_size);
    Array* arr = array_create(size);
    if (!arr) return nullptr;

    for (size_t i = 0; i < size; ++i) {
        Data val;
        if (!(stream >> val)) {
            array_delete(arr);
            return nullptr;
        }
        array_set(arr, i, val);
    }
    return arr;
}