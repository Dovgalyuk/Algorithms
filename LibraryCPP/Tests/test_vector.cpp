#include <iostream>
#include "vector.h"

using namespace std;

#define CHECK(cond, msg)                         \
    if (!(cond))                                 \
    {                                            \
        cout << "FAILED: " << msg << "\n";  \
        vector_delete(vector);                   \
        return 1;                                \
    }

int main()
{
    Vector *vector = vector_create();

    CHECK(vector_size(vector) == 0, "new vector is not empty");

    vector_resize(vector, 5);
    CHECK(vector_size(vector) == 5, "size after resize(5)");
    for (size_t i = 0; i < 5; ++i)
        vector_set(vector, i, (Data)(i * 10));
    for (size_t i = 0; i < 5; ++i)
        CHECK(vector_get(vector, i) == (Data)(i * 10), "get after set");

    vector_set(vector, 2, -7);
    CHECK(vector_get(vector, 2) == -7, "overwrite element");

    vector_resize(vector, 100);
    CHECK(vector_size(vector) == 100, "size after resize(100)");
    CHECK(vector_get(vector, 0) == 0 && vector_get(vector, 1) == 10
        && vector_get(vector, 2) == -7 && vector_get(vector, 4) == 40,
        "old elements lost after growing");

    vector_resize(vector, 3);
    CHECK(vector_size(vector) == 3, "size after resize(3)");
    CHECK(vector_get(vector, 1) == 10 && vector_get(vector, 2) == -7,
        "elements lost after shrinking");

    vector_resize(vector, 0);
    CHECK(vector_size(vector) == 0, "size after resize(0)");
    vector_resize(vector, 1);
    vector_set(vector, 0, 42);
    CHECK(vector_get(vector, 0) == 42, "reuse after resize(0)");

    const size_t N = 1000000;
    vector_resize(vector, 0);
    for (size_t i = 0; i < N; ++i)
    {
        vector_resize(vector, i + 1);
        vector_set(vector, i, (Data)i);
    }
    CHECK(vector_size(vector) == N, "size after many appends");
    for (size_t i = 0; i < N; ++i)
        CHECK(vector_get(vector, i) == (Data)i, "value after many appends");

    vector_delete(vector);
    cout << "vector: OK\n";
    return 0;
}