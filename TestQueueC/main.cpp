#include <iostream>
#include "queue.h"

void additional_tests(Queue* queue)
{
    for (int i = 0; i < 100; i++)
    {
        queue_insert(queue, i);
    }
    for (int i = 0; i < 50; i++)
    {
        if (queue_get(queue) != i)
            std::cout << "Invalid element of the queue in test2\n";
        queue_remove(queue);
    }
    for (int i = 100; i < 150; i++)
    {
        queue_insert(queue, i);
    }
    for (int i = 50; i < 150; i++)
    {
        if (queue_get(queue) != i)
            std::cout << "Invalid element of the queue in test4\n";
        queue_remove(queue);
    }
}

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

    additional_tests(queue);

    queue_delete(queue);
}
