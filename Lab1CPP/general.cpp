#include "general.h"

Array* array_create_and_read(std::ifstream& input) {
    size_t size;
    if (!(input >> size)) {
        return nullptr;
    }

    Array* arr = array_create(size);
    for (size_t i = 0; i < size; i++) {
        if (!(input >> arr->data[i])) {
            array_delete(arr);
            return nullptr;
        }
    }
    return arr;
}