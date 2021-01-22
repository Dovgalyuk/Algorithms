#include <iostream>
#include "queue.h"

int main()
{
    Queue *queue = queue_create();

    queue_insert(queue, 1);
    queue_insert(queue, 2);
    queue_insert(queue, 3);

    if (queue_get(queue) != 1)
        std::cout << "Invalid first element of the queue\n";

    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_remove(queue);

    if (queue_get(queue) != 2)
        std::cout << "Invalid second element of the queue\n";

    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_remove(queue);

    if (queue_get(queue) != 3)
        std::cout << "Invalid third element of the queue\n";

    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_insert(queue, 4);
    while (!queue_empty(queue))
    {
        std::cout << "Get: " << queue_get(queue) << "\n";
        queue_remove(queue);
    }

    std::cout << "=======================================" << std::endl;

    for (int i = 0; i < 20; i++)
    {
        queue_insert(queue, i);
    }
    for (int i = 0; i < 10; i++)
    {
        std::cout << i << " | " << "Get: " << queue_get(queue) << std::endl;
        queue_remove(queue);
    }
    for (int i = 0; i < 40; i++)
    {
        queue_insert(queue, i);
    }
    while (!queue_empty(queue))
    {
        std::cout << "Get: " << queue_get(queue) << "\n";
        queue_remove(queue);
    }

    queue_delete(queue);
}
