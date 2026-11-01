#include <deque>
#include <limits>
#include <memory>
#include <random>
#include <stdexcept>
#include "queue.h"
#include "vector.h"

void check(bool condition)
{
    if (!condition)
        throw std::runtime_error("Container check failed");
}

int main()
{
    std::unique_ptr<Vector, decltype(&vector_delete)> vector(vector_create(), vector_delete);
    check(vector_size(vector.get()) == 0);
    vector_resize(vector.get(), 0);
    for (size_t i = 1; i <= 100000; ++i)
    {
        vector_resize(vector.get(), i);
        check(vector_get(vector.get(), i - 1) == 0);
        vector_set(vector.get(), i - 1, static_cast<int>(i));
    }
    vector_resize(vector.get(), 3);
    vector_resize(vector.get(), 8);
    for (size_t i = 0; i < 8; ++i)
        check(vector_get(vector.get(), i) == (i < 3 ? static_cast<int>(i + 1) : 0));
    bool get_failed = false;
    bool set_failed = false;
    bool resize_failed = false;
    try { vector_get(vector.get(), 8); }
    catch (const std::out_of_range &) { get_failed = true; }
    try { vector_set(vector.get(), 8, 42); }
    catch (const std::out_of_range &) { set_failed = true; }
    try { vector_resize(vector.get(), std::numeric_limits<size_t>::max()); }
    catch (const std::length_error &) { resize_failed = true; }
    check(get_failed && set_failed && resize_failed && vector_size(vector.get()) == 8);
    vector_resize(vector.get(), 0);
    vector_resize(vector.get(), 1);
    check(vector_get(vector.get(), 0) == 0);

    std::unique_ptr<Queue, decltype(&queue_delete)> queue(queue_create(), queue_delete);
    check(queue_empty(queue.get()));
    bool queue_get_failed = false;
    bool remove_failed = false;
    try { queue_get(queue.get()); }
    catch (const std::out_of_range &) { queue_get_failed = true; }
    try { queue_remove(queue.get()); }
    catch (const std::out_of_range &) { remove_failed = true; }
    check(queue_get_failed && remove_failed);

    // Fill, wrap, and then grow a full buffer whose first index is nonzero.
    for (int i = 0; i < 4; ++i)
        queue_insert(queue.get(), i);
    for (int i = 0; i < 2; ++i)
    {
        check(queue_get(queue.get()) == i);
        queue_remove(queue.get());
    }
    for (int i = 4; i < 100000; ++i)
        queue_insert(queue.get(), i);
    for (int i = 2; i < 100000; ++i)
    {
        check(queue_get(queue.get()) == i);
        queue_remove(queue.get());
    }
    check(queue_empty(queue.get()));

    // Independent FIFO reference with reproducible mixed insert/remove operations.
    std::deque<int> reference;
    std::mt19937 generator(20261101);
    for (int i = 0; i < 200000; ++i)
    {
        if (reference.empty() || generator() % 2 == 0)
        {
            int value = static_cast<int>(generator() % 1000000);
            queue_insert(queue.get(), value);
            reference.push_back(value);
        }
        else
        {
            check(queue_get(queue.get()) == reference.front());
            queue_remove(queue.get());
            reference.pop_front();
        }
        check(queue_empty(queue.get()) == reference.empty());
    }
    while (!reference.empty())
    {
        check(queue_get(queue.get()) == reference.front());
        queue_remove(queue.get());
        reference.pop_front();
    }
    check(queue_empty(queue.get()));
    // A long-lived queue repeatedly wraps without growing with total insertions.
    queue_insert(queue.get(), 0);
    for (int i = 1; i <= 200000; ++i)
    {
        queue_insert(queue.get(), i);
        check(queue_get(queue.get()) == i - 1);
        queue_remove(queue.get());
    }
    check(queue_get(queue.get()) == 200000);
    // Leave a nonempty queue for the destructor.
}
