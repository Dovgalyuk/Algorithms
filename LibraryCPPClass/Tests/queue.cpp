#include <iostream>
#include "queue.h"

int main()
{
    Queue *queue = new Queue();

    queue->insert(1);
    queue->insert(2);
    queue->insert(3);

    if (queue->get() != 1)
    {
        std::cout << "Invalid first element of the queue\n";
        return 1;
    }

    std::cout << "Get: " << queue->get() << "\n";
    queue->remove();

    if (queue->get() != 2)
    {
        std::cout << "Invalid second element of the queue\n";
        return 1;
    }

    std::cout << "Get: " << queue->get() << "\n";
    queue->remove();

    if (queue->get() != 3)
    {
        std::cout << "Invalid third element of the queue\n";
        return 1;
    }

    std::cout << "Get: " << queue->get() << "\n";
    queue->insert(4);
    while (!queue->empty())
    {
        std::cout << "Get: " << queue->get() << "\n";
        queue->remove();
    }

    // Performance test
    for (int i = 1 ; i <= 10000000 ; ++i)
    {
        queue->insert(i);
    }

    delete queue;
}
