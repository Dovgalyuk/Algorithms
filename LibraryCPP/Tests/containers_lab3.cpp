#include <iostream>
#include "vector.h"
#include "queue.h"

namespace {
bool test_vector()
{
    Vector* values = vector_create();
    if (vector_size(values) != 0) return false;

    // Growth through multiple capacity boundaries, without losing previous data.
    for (size_t i = 0; i < 128; ++i) {
        vector_resize(values, i + 1);
        vector_set(values, i, static_cast<Data>(i * 3));
    }
    for (size_t i = 0; i < 128; ++i) {
        if (vector_get(values, i) != static_cast<Data>(i * 3)) return false;
    }

    // Shrink and grow again: retained elements must be unchanged.
    vector_resize(values, 7);
    if (vector_size(values) != 7) return false;
    vector_resize(values, 40);
    for (size_t i = 0; i < 7; ++i) {
        if (vector_get(values, i) != static_cast<Data>(i * 3)) return false;
    }
    vector_set(values, 39, -17);
    if (vector_get(values, 39) != -17) return false;
    vector_resize(values, 0);
    const bool ok = vector_size(values) == 0;
    vector_delete(values);
    return ok;
}

bool test_queue()
{
    Queue* q = queue_create();
    if (!queue_empty(q)) return false;
    // Removing an empty queue should not break subsequent insertions.
    queue_remove(q);
    if (!queue_empty(q)) return false;

    // FIFO with a wrapped buffer followed by buffer growth.
    queue_insert(q, 10);
    queue_insert(q, 20);
    if (queue_get(q) != 10) return false;
    queue_remove(q);
    queue_insert(q, 30);
    queue_insert(q, 40);
    if (queue_get(q) != 20) return false;
    queue_remove(q);
    if (queue_get(q) != 30) return false;
    queue_remove(q);
    if (queue_get(q) != 40) return false;
    queue_remove(q);
    if (!queue_empty(q)) return false;

    // Several resizings and full draining without loss or reordering.
    for (int i = 0; i < 1024; ++i) queue_insert(q, i);
    for (int i = 0; i < 1024; ++i) {
        if (queue_empty(q) || queue_get(q) != i) return false;
        queue_remove(q);
    }
    if (!queue_empty(q)) return false;
    queue_insert(q, -42);
    const bool ok = !queue_empty(q) && queue_get(q) == -42;
    queue_delete(q);
    return ok;
}
}

int main()
{
    if (!test_vector()) {
        std::cerr << "Vector container test failed\n";
        return 1;
    }
    if (!test_queue()) {
        std::cerr << "Queue container test failed\n";
        return 1;
    }
    std::cout << "Lab 3 vector and queue container tests passed\n";
    return 0;
}
