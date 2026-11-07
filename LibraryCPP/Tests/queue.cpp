#include <iostream>
#include "queue.h"

int main()
{
    Queue* queue = queue_create();

    if (queue == nullptr || !queue_empty(queue))
    {
        std::cout << "Queue creation error\n";
        queue_delete(queue);
        return 1;
    }

    for (int i = 0; i < 8; ++i)
        queue_insert(queue, i);

    for (int i = 0; i < 5; ++i)
    {
        if (queue_get(queue) != i)
        {
            std::cout << "Queue order error\n";
            queue_delete(queue);
            return 1;
        }
        queue_remove(queue);
    }

    for (int i = 8; i < 14; ++i)
        queue_insert(queue, i);

    for (int i = 5; i < 14; ++i)
    {
        if (queue_empty(queue) || queue_get(queue) != i)
        {
            std::cout << "Queue order or resize error\n";
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

    for (int i = 0; i < 1000; ++i)
        queue_insert(queue, i);

    for (int i = 0; i < 1000; ++i)
    {
        if (queue_get(queue) != i)
        {
            std::cout << "Queue large-data error\n";
            queue_delete(queue);
            return 1;
        }
        queue_remove(queue);
    }

    queue_delete(queue);
    std::cout << "Queue tests passed\n";
    return 0;
}
