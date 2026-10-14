#include "vector.h"

int main() {
    Vector* v = vector_create();

    vector_resize(v, 5);
    if (vector_size(v) != 5) return 1;

    for (size_t i = 0; i < vector_size(v); ++i)
        vector_set(v, i, (int)i * 2);

    for (size_t i = 0; i < vector_size(v); ++i)
        if (vector_get(v, i) != (int)i * 2) return 1;

    vector_resize(v, 100);
    if (vector_size(v) != 100) return 1;

    for (size_t i = 0; i < 100; ++i)
        vector_set(v, i, (int)i);

    for (size_t i = 0; i < 100; ++i)
        if (vector_get(v, i) != (int)i) return 1;

    vector_resize(v, 3);
    if (vector_size(v) != 3) return 1;

    vector_delete(v);
    return 0;
}
