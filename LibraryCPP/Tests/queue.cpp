#include <iostream>
#include "queue.h"

static bool remove_expected(Queue *queue, Data expected)
{
    if (queue_empty(queue) || queue_get(queue) != expected)
    {
        std::cerr << "Expected queue front: " << expected << "\n";
        return false;
    }

    queue_remove(queue);
    return true;
}

static bool check_empty(const Queue *queue)
{
    if (!queue_empty(queue))
    {
        std::cerr << "Queue should be empty\n";
        return false;
    }

    return true;
}

static bool test_queue(Queue *queue)
{
    if (!check_empty(queue))
        return false;

    for (Data value = 1; value <= 4; ++value)
        queue_insert(queue, value);

    for (Data value = 1; value <= 2; ++value)
    {
        if (!remove_expected(queue, value))
            return false;
    }

    for (Data value = 5; value <= 7; ++value)
        queue_insert(queue, value);

    for (Data value = 3; value <= 7; ++value)
    {
        if (!remove_expected(queue, value))
            return false;
    }

    if (!check_empty(queue))
        return false;

    queue_remove(queue);
    for (Data value = -1; value <= 1; ++value)
        queue_insert(queue, value);

    for (Data value = -1; value <= 1; ++value)
    {
        if (!remove_expected(queue, value))
            return false;
    }

    if (!check_empty(queue))
        return false;

    const int element_count = 10000000;
    for (Data value = 1; value <= element_count; ++value)
        queue_insert(queue, value);

    for (Data value = 1; value <= element_count; ++value)
    {
        if (!remove_expected(queue, value))
            return false;
    }

    return check_empty(queue);
}

int main()
{
    Queue *queue = queue_create();
    bool passed = test_queue(queue);
    queue_delete(queue);
    return passed ? 0 : 1;
}
