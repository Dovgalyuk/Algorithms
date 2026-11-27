#include <iostream>
#include <utility>
#include "PriorityQueue.h"

typedef PriorityQueue<int> MyPQueue;
typedef PriorityQueue<std::pair<int, size_t>> PairPQueue;

int main()
{
    MyPQueue pq;
    if (!pq.empty())
    {
        std::cout << "Empty queue error\n";
        return 1;
    }
    if (pq.size() != 0)
    {
        std::cout << "Invalid empty size\n";
        return 1;
    }

    pq.push(5);
    pq.push(3);
    pq.push(7);
    pq.push(1);
    pq.push(4);

    if (pq.size() != 5)
    {
        std::cout << "Invalid size after push\n";
        return 1;
    }
    if (pq.top() != 1)
    {
        std::cout << "Invalid top element (expected 1)\n";
        return 1;
    }

    pq.pop();
    if (pq.top() != 3)
    {
        std::cout << "Invalid top after pop (expected 3)\n";
        return 1;
    }
    pq.pop();
    if (pq.top() != 4)
    {
        std::cout << "Invalid top after pop (expected 4)\n";
        return 1;
    }
    pq.pop();
    if (pq.top() != 5)
    {
        std::cout << "Invalid top after pop (expected 5)\n";
        return 1;
    }
    pq.pop();
    if (pq.top() != 7)
    {
        std::cout << "Invalid top after pop (expected 7)\n";
        return 1;
    }
    pq.pop();
    if (!pq.empty())
    {
        std::cout << "Queue should be empty\n";
        return 1;
    }

    pq.pop();
    pq.pop();
    if (!pq.empty())
    {
        std::cout << "Queue should still be empty\n";
        return 1;
    }

    pq.push(42);
    if (pq.top() != 42)
    {
        std::cout << "Invalid single element\n";
        return 1;
    }
    pq.pop();
    if (!pq.empty())
    {
        std::cout << "Queue should be empty after single pop\n";
        return 1;
    }

    pq.push(10);
    pq.push(20);
    pq = pq;
    if (pq.top() != 10)
    {
        std::cout << "Self-assignment error\n";
        return 1;
    }
    if (pq.size() != 2)
    {
        std::cout << "Invalid size after self-assignment\n";
        return 1;
    }

    MyPQueue copy = pq;
    if (copy.size() != 2)
    {
        std::cout << "Invalid copy size\n";
        return 1;
    }
    if (copy.top() != 10)
    {
        std::cout << "Invalid copy top\n";
        return 1;
    }

    pq.pop();
    pq.pop();
    pq.push(100);
    if (copy.top() != 10)
    {
        std::cout << "Copy is not independent\n";
        return 1;
    }

    PairPQueue pairPq;
    pairPq.push(std::make_pair(10, 0));
    pairPq.push(std::make_pair(5, 1));
    pairPq.push(std::make_pair(15, 2));
    pairPq.push(std::make_pair(5, 3));

    if (pairPq.top().first != 5)
    {
        std::cout << "Invalid pair top distance\n";
        return 1;
    }
    if (pairPq.top().second != 1)
    {
        std::cout << "Invalid pair top index (expected 1)\n";
        return 1;
    }

    PairPQueue perfPq;
    for (int i = 100000; i >= 1; --i)
    {
        perfPq.push(std::make_pair(i, i));
    }
    if (perfPq.size() != 100000)
    {
        std::cout << "Invalid performance queue size\n";
        return 1;
    }

    long long sum = 0;
    int prev_dist = 0;
    while (!perfPq.empty())
    {
        int d = perfPq.top().first;
        if (d < prev_dist)
        {
            std::cout << "Performance test: order violated\n";
            return 1;
        }
        prev_dist = d;
        sum += d;
        perfPq.pop();
    }
    if (sum != 5000050000LL)
    {
        std::cout << "Invalid sum: " << sum << "\n";
        return 1;
    }

    std::cout << "All priority queue tests passed\n";
    return 0;
}