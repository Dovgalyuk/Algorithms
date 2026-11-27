#include <iostream>
#include <deque>
#include "queue.h"

int main()
{
    Queue *queue = queue_create();
    if (!queue_empty(queue))
        return 1;
    queue_remove(queue);

    // Fill capacity 8, wrap the tail, then grow while head != 0.
    for (int i = 0; i < 8; ++i)
        queue_insert(queue, i);
    for (int i = 0; i < 5; ++i)
    {
        if (queue_get(queue) != i)
            return 1;
        queue_remove(queue);
    }
    for (int i = 8; i < 20; ++i)
        queue_insert(queue, i);
    for (int i = 5; i < 20; ++i)
    {
        if (queue_get(queue) != i)
            return 1;
        queue_remove(queue);
    }
    if (!queue_empty(queue))
        return 1;

    queue_insert(queue, 1);
    queue_insert(queue, 2);
    queue_insert(queue, 3);

    if (queue_get(queue) != 1)
    {
        std::cout << "Invalid first element of the queue\n";
        return 1;
    }

    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_remove(queue);

    if (queue_get(queue) != 2)
    {
        std::cout << "Invalid second element of the queue\n";
        return 1;
    }

    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_remove(queue);

    if (queue_get(queue) != 3)
    {
        std::cout << "Invalid third element of the queue\n";
        return 1;
    }

    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_insert(queue, 4);
    while (!queue_empty(queue))
    {
        std::cout << "Get: " << queue_get(queue) << "\n";
        queue_remove(queue);
    }

    // Compare repeated wraparound, expansion and reuse against a reference FIFO.
    std::deque<Data> expected;
    unsigned int state = 42;
    for (int i = 0; i < 20000; ++i)
    {
        state = state * 1664525u + 1013904223u;
        if (expected.empty() || state % 3 != 0)
        {
            queue_insert(queue, i);
            expected.push_back(i);
        }
        else
        {
            if (queue_get(queue) != expected.front())
                return 1;
            queue_remove(queue);
            expected.pop_front();
        }
    }
    while (!expected.empty())
    {
        if (queue_get(queue) != expected.front())
            return 1;
        queue_remove(queue);
        expected.pop_front();
    }
    if (!queue_empty(queue))
        return 1;

    // Performance test
    queue_insert(queue, 0);
    for (int i = 1 ; i <= 1000000 ; ++i)
    {
        queue_insert(queue, i);
    }

    for (int i = 1 ; i <= 1000000 ; ++i)
    {
        queue_remove(queue);
    }

    for (int i = 1 ; i <= 1000000 ; ++i)
    {
        queue_insert(queue, i);
        queue_remove(queue);
    }

    queue_delete(queue);

    queue = queue_create();
    queue_insert(queue, 0);
    for (int i = 1 ; i <= 100000 ; ++i)
    {
        int cnt = 1 + i % 20;
        for (int j = 0 ; j < cnt ; ++j) {
            queue_insert(queue, i);
        }
        for (int j = 0 ; j < cnt ; ++j) {
            queue_remove(queue);
        }
    }

    queue_delete(queue);
}
