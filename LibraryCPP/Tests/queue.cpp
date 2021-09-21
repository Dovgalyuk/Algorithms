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
    int  number = 3;
    while (!queue_empty(queue))
    {
        std::cout << "Get: " << queue_get(queue) << "\n";
        if (queue_get(queue) != number++) {
            std::cout << "Invalid element\n";
            return 1;
        }
        queue_remove(queue);
    }

    if (number != 5) {
        std::cout << "Queue is not empty!\n";
        return 1;
    }

    queue_delete(queue);
}
