#include <iostream>
#include "queue.h"

int main()
{
    Queue *queue = queue_create();

    queue_insert(queue, 1);
    queue_insert(queue, 2);
    queue_insert(queue, 3);

    if (queue_get(queue) != 1)
    {
        std::cout << "Invalid first element of the queue\n";
        queue_delete(queue);
        return 1;
    }

    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_remove(queue);

    if (queue_get(queue) != 2)
    {
        std::cout << "Invalid second element of the queue\n";
        queue_delete(queue);
        return 1;
    }

    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_remove(queue);

    if (queue_get(queue) != 3)
    {
        std::cout << "Invalid third element of the queue\n";
        queue_delete(queue);
        return 1;
    }

    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_insert(queue, 4);

    while (!queue_empty(queue))
    {
        std::cout << "Get: " << queue_get(queue) << "\n";
        queue_remove(queue);
    }

    // Check circular movement and buffer growth.
    for (int i = 1; i <= 4; ++i)
        queue_insert(queue, i);

    queue_remove(queue);
    queue_remove(queue);

    queue_insert(queue, 5);
    queue_insert(queue, 6);
    queue_insert(queue, 7);

    for (int i = 3; i <= 7; ++i)
    {
        if (queue_get(queue) != i)
        {
            std::cout << "Invalid queue order after resize\n";
            queue_delete(queue);
            return 1;
        }

        queue_remove(queue);
    }

    if (!queue_empty(queue))
    {
        std::cout << "Queue should be empty\n";
        queue_delete(queue);
        return 1;
    }

    // Performance test.
    for (int i = 1; i <= 10000000; ++i)
        queue_insert(queue, i);

    queue_delete(queue);
}
