#include <iostream>
#include "queue.h"

int queue_get_int(Queue *q)
{
    return *(int*)queue_get(q);
}

int main()
{
    Queue *queue = queue_create([](void *p) { delete (int*)p; });

    queue_insert(queue, new int(1));
    queue_insert(queue, new int(2));
    queue_insert(queue, new int(3));

    if (queue_get_int(queue) != 1)
    {
        std::cout << "Invalid first element of the queue\n";
        return 1;
    }

    std::cout << "Get: " << queue_get_int(queue) << "\n";
    queue_remove(queue);

    if (queue_get_int(queue) != 2)
    {
        std::cout << "Invalid second element of the queue\n";
        return 1;
    }

    std::cout << "Get: " << queue_get_int(queue) << "\n";
    queue_remove(queue);

    if (queue_get_int(queue) != 3)
    {
        std::cout << "Invalid third element of the queue\n";
        return 1;
    }

    std::cout << "Get: " << queue_get_int(queue) << "\n";
    queue_insert(queue, new int(4));
    while (!queue_empty(queue))
    {
        std::cout << "Get: " << queue_get_int(queue) << "\n";
        queue_remove(queue);
    }

    queue_delete(queue);
}
