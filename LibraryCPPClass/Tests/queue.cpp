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

    queue->insert(10);
    queue->insert(20);
    Queue queue_copy(*queue);

    if (queue_copy.get() != queue->get())
    {
        std::cout << "Copy constructor failed\n";
        return 1;
    }

    Queue assigned_queue;
    assigned_queue = *queue;
    if (assigned_queue.get() != queue->get())
    {
        std::cout << "Assignment operator failed\n";
        return 1;
    }

    while (!queue->empty())
    {
        queue->remove();
    }

    try
    {
        queue->get();
        std::cout << "Failed to catch get on empty queue\n";
        return 1;
    }
    catch (const std::out_of_range &)
    {
        std::cout << "Caught get on empty queue\n";
    }

    try
    {
        queue->remove();
        std::cout << "Failed to catch remove on empty queue\n";
        return 1;
    }
    catch (const std::out_of_range &)
    {
        std::cout << "Caught remove on empty queue\n";
    }

    delete queue;
}