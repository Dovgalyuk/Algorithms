#include <iostream>
#include "queue.h"

int main()
{
    Queue *queue = queue_create();

    queue_insert(queue, {1, 0, 0});
    queue_insert(queue, {2, 0, 0});
    queue_insert(queue, {3, 0, 0});

    if (queue_get(queue).x != 1)
    {
        std::cout << "Invalid first element of the queue\n";
        return 1;
    }

    Position pos = queue_get(queue);
    std::cout << "Get: " << pos.x << ", " << pos.y << ", " << pos.z << "\n";
    queue_remove(queue);

    if (queue_get(queue).x != 2)
    {
        std::cout << "Invalid second element of the queue\n";
        return 1;
    }

    pos = queue_get(queue);
    std::cout << "Get: " << pos.x << ", " << pos.y << ", " << pos.z << "\n";
    queue_remove(queue);

    if (queue_get(queue).x != 3)
    {
        std::cout << "Invalid third element of the queue\n";
        return 1;
    }

    pos = queue_get(queue);
    std::cout << "Get: " << pos.x << ", " << pos.y << ", " << pos.z << "\n";
    queue_remove(queue);

    queue_insert(queue, {4, 0, 0});
    while (!queue_empty(queue))
    {
        pos = queue_get(queue);
        std::cout << "Get: " << pos.x << ", " << pos.y << ", " << pos.z << "\n";
        queue_remove(queue);
    }

    // Performance test
    queue_insert(queue, {0, 0, 0});
    for (int i = 1; i <= 1000000; ++i)
    {
        queue_insert(queue, {static_cast<size_t>(i), 0, 0});
    }

    for (int i = 1; i <= 1000000; ++i)
    {
        queue_remove(queue);
    }

    for (int i = 1; i <= 1000000; ++i)
    {
        queue_insert(queue, {static_cast<size_t>(i), 0, 0});
        queue_remove(queue);
    }

    queue_delete(queue);

    queue = queue_create();
    queue_insert(queue, {0, 0, 0});

    for (int i = 1; i <= 100000; ++i)
    {
        int cnt = 1 + i % 20;

        for (int j = 0; j < cnt; ++j)
            queue_insert(queue, {static_cast<size_t>(i), 0, 0});

        for (int j = 0; j < cnt; ++j)
            queue_remove(queue);
    }

    queue_delete(queue);
}