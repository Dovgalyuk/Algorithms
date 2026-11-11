#include "queue.h"
#include <iostream>

int main()
{
    Queue<int> q;
    if (!q.empty()) {
        std::cerr << "New queue should be empty\n";
        return 1;
    }

    q.insert(10);
    if (q.empty() || q.get() != 10) {
        std::cerr << "Insert/get failed\n";
        return 2;
    }
    q.remove();
    if (!q.empty()) {
        std::cerr << "Remove failed\n";
        return 3;
    }

    // Repeated remove/insert forces wraparound; many inserts force growth.
    for (int i = 0; i < 100; ++i)
        q.insert(i);
    for (int i = 0; i < 60; ++i) {
        if (q.empty() || q.get() != i) {
            std::cerr << "Order error while removing " << i << '\n';
            return 4;
        }
        q.remove();
    }
    for (int i = 100; i < 500; ++i)
        q.insert(i);

    // Check deep copies while buffer is wrapped / expanded.
    Queue<int> copy(q);
    Queue<int> assigned;
    assigned = q;
    assigned = assigned;

    for (int i = 60; i < 500; ++i) {
        if (q.empty() || copy.empty() || assigned.empty() ||
            q.get() != i || copy.get() != i || assigned.get() != i) {
            std::cerr << "Queue order or copy error at " << i << '\n';
            return 5;
        }
        q.remove();
        copy.remove();
        assigned.remove();
    }
    if (!q.empty() || !copy.empty() || !assigned.empty()) {
        std::cerr << "Queues must be empty\n";
        return 6;
    }

    std::cout << "Queue: OK\n";
    return 0;
}
