#include <stdexcept>
#include <iostream>
#include "queue.h"

bool checkQueue()
{
    Queue queue;
    if (!queue.empty()) return false;
    try { queue.get(); return false; }
    catch (const std::out_of_range &) {}
    try { queue.remove(); return false; }
    catch (const std::out_of_range &) {}
    for (int i = 0; i < 4; i++) queue.insert(i);
    queue.remove();
    queue.remove();
    queue.insert(4);
    queue.insert(5);
    Queue wrapped(queue);
    queue.insert(6); // Expand while the stored elements wrap around the buffer.
    Queue assigned;
    assigned.insert(-1);
    assigned = queue;
    queue = queue;
    for (int i = 2; i <= 6; i++)
    {
        if (queue.get() != i || assigned.get() != i) return false;
        queue.remove();
        assigned.remove();
    }
    for (int i = 2; i <= 5; i++)
    {
        if (wrapped.get() != i) return false;
        wrapped.remove();
    }
    if (!queue.empty() || !assigned.empty() || !wrapped.empty()) return false;
    for (int i = 0; i < 1000; i++)
    {
        queue.insert(i);
        if (queue.get() != i) return false;
        queue.remove();
    }
    assigned = queue;
    return assigned.empty();
}
int main()
{
    if (!checkQueue()) return 1;
    Queue *queue = new Queue();

    queue->insert(1);
    queue->insert(2);
    queue->insert(3);

    *queue = *queue;

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
