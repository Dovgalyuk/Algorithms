#include <iostream>
#include "pqueue.h"

int main()
{
    PriorityQueue* pq = pqueue_create();
    if (!pqueue_empty(pq))
    {
        std::cout << "Queue must be empty after creation\n";
        return 1;
    }

    int dist1[3] = { 5, 3, 7 };

    pqueue_push(pq, 0, dist1[0]); 
    pqueue_push(pq, 1, dist1[1]); 
    pqueue_push(pq, 2, dist1[2]); 

    int a = pqueue_pop(pq);
    if (a != 1)
    {
        std::cout << "Invalid pop order (expected 1, got " << a << ")\n";
        return 1;
    }

    int b = pqueue_pop(pq);
    if (b != 0)
    {
        std::cout << "Invalid pop order (expected 0, got " << b << ")\n";
        return 1;
    }

    int c = pqueue_pop(pq);
    if (c != 2)
    {
        std::cout << "Invalid pop order (expected 2, got " << c << ")\n";
        return 1;
    }

    if (!pqueue_empty(pq))
    {
        std::cout << "Queue must be empty after popping everything\n";
        return 1;
    }

    int dist2[5] = { 10, 8, 6, 4, 2 };

    pqueue_push(pq, 0, dist2[0]);
    pqueue_push(pq, 1, dist2[1]);
    pqueue_push(pq, 2, dist2[2]);
    pqueue_push(pq, 3, dist2[3]);
    pqueue_push(pq, 4, dist2[4]);

    int expected_order[5] = { 4, 3, 2, 1, 0 };
    for (int i = 0; i < 5; i++)
    {
        int x = pqueue_pop(pq);
        if (x != expected_order[i])
        {
            std::cout << "Invalid pop: expected " << expected_order[i]
                << ", got " << x << "\n";
            return 1;
        }
    }

    if (!pqueue_empty(pq))
    {
        std::cout << "Queue must be empty\n";
        return 1;
    }

    int dist3[4] = { 100, 90, 80, 70 };

    pqueue_push(pq, 2, dist3[2]);
    pqueue_push(pq, 0, dist3[0]);
    pqueue_push(pq, 1, dist3[1]);

    int x1 = pqueue_pop(pq);
    int x2 = pqueue_pop(pq);
    int x3 = pqueue_pop(pq);

    if (!(x1 == 2 && x2 == 1 && x3 == 0))
    {
        std::cout << "Invalid popping order in multi-op test\n";
        return 1;
    }

    pqueue_delete(pq);

    std::cout << "PriorityQueue test passed!\n";
    return 0;
}
