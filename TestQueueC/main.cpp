#include <iostream>
#include "queue.h"

int main()
{
    Queue *queue = new Queue();

    queue->Insert(1);
    queue->Insert(2);
    queue->Insert(3);

    if (queue->Get() != 1)
        std::cout << "Invalid first element of the queue\n";

    std::cout << "Get: " << queue->Get() << "\n";
    queue->Remove();

    if (queue->Get() != 2)
        std::cout << "Invalid second element of the queue\n";

    std::cout << "Get: " << queue->Get() << "\n";
    queue->Remove();

    if (queue->Get() != 3)
        std::cout << "Invalid third element of the queue\n";

    std::cout << "Get: " << queue->Get() << "\n";
    queue->Insert(4);
    while (!queue->IsEmpty())
    {
        std::cout << "Get: " << queue->Get() << "\n";
        queue->Remove();
    }

    delete queue;
}
