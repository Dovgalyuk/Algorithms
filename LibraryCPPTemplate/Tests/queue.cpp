#include <iostream>
#include "queue.h"

typedef Queue<int> MyQueue;

int main()
{
    MyQueue *queue = new MyQueue();

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

    MyQueue copy(*queue);
    for (int i = 1 ; i <= 10000000 ; ++i)
    {
        if (copy.empty())
            return 1;
        if (copy.get() != i)
        {
            std::cout << "Get error: " << i << " " << queue->get() << "\n";
            return 1;
        }
        copy.remove();
    }

    delete queue;
}
