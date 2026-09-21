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
