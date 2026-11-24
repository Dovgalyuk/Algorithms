#include <iostream>
#include <stdexcept>
#include "queue.h"

int main()
{
    Queue* q = queue_create();

    if (!queue_empty(q))
        return 1;

    queue_insert(q, 10);
    queue_insert(q, 20);
    queue_insert(q, 30);

    if (queue_empty(q))
        return 1;

    if (queue_get(q) != 10)
        return 1;

    queue_remove(q);

    if (queue_get(q) != 20)
        return 1;

    queue_remove(q);

    if (queue_get(q) != 30)
        return 1;

    queue_remove(q);

    if (!queue_empty(q))
        return 1;

    bool exceptionCaught = false;

    try
    {
        queue_get(q);
    }
    catch (const std::out_of_range&)
    {
        exceptionCaught = true;
    }

    if (!exceptionCaught)
        return 1;

    for (int i = 0; i < 1000; ++i)
        queue_insert(q, i);

    for (int i = 0; i < 500; ++i)
    {
        if (queue_get(q) != i)
            return 1;

        queue_remove(q);
    }

    for (int i = 1000; i < 1500; ++i)
        queue_insert(q, i);

    for (int i = 500; i < 1500; ++i)
    {
        if (queue_empty(q) || queue_get(q) != i)
            return 1;

        queue_remove(q);
    }

    if (!queue_empty(q))
        return 1;

    queue_delete(q);

    std::cout << "Queue tests passed\n";
    return 0;
}
