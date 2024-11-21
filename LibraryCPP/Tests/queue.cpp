#include <iostream>
#include "queue.h"

int main()
{
    Queue *queue = queue_create();

    queue_insert(queue, {1,1});
    queue_insert(queue, {2,2});
    queue_insert(queue, {3,3});

    if (queue_get(queue).first != 1)
    {
        std::cout << "Invalid first element of the queue\n";
        return 1;
    }

    std::cout << "Get: " << queue_get(queue).first << "\n";
    queue_remove(queue);

    if (queue_get(queue).first != 2)
    {
        std::cout << "Invalid second element of the queue\n";
        return 1;
    }

    std::cout << "Get: " << queue_get(queue).first << "\n";
    queue_remove(queue);

    if (queue_get(queue).first != 3)
    {
        std::cout << "Invalid third element of the queue\n";
        return 1;
    }

    std::cout << "Get: " << queue_get(queue).first << "\n";
    queue_insert(queue, {4,4});
    while (!queue_empty(queue))
    {
        std::cout << "Get: " << queue_get(queue).first << "\n";
        queue_remove(queue);
    }

    // Performance test
    for (int i = 1 ; i <= 10000000 ; ++i)
    {
        queue_insert(queue, {i,i});
    }

    queue_delete(queue);
}
