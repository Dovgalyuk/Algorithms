#include <iostream>
#include "queue.h"

int main()
{
    Queue *queue = queue_create();

    queue_insert(queue, 1);
    queue_insert(queue, 2);
    queue_insert(queue, 3);

    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_remove(queue);
    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_remove(queue);
    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_insert(queue, 4);
    while (!queue_empty(queue))
    {
        std::cout << "Get: " << queue_get(queue) << "\n";
        queue_remove(queue);
    }

    queue_delete(queue);
}
