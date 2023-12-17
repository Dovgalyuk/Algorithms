#include "priorityqueue.h"
#include <iostream>

void testIsEmpty() {
    PriorityQueue<int> pq;
    if (pq.isEmpty() != true) {
        std::cerr << "Test failed: testIsEmpty (queue should be empty initially)" << std::endl;
        exit(1);
    }

    pq.insert(10, 1);
    if (pq.isEmpty() != false) {
        std::cerr << "Test failed: testIsEmpty (queue should not be empty after insertion)" << std::endl;
        exit(1);
    }
}

void testInsertAndExtractMin() {
    PriorityQueue<int> pq;
    pq.insert(20, 2);
    pq.insert(10, 1);
    pq.insert(30, 3);

    if (pq.extractMin() != 10) {
        std::cerr << "Test failed: testInsertAndExtractMin (incorrect min value after insertions)" << std::endl;
        exit(1);
    }

    if (pq.extractMin() != 20) {
        std::cerr << "Test failed: testInsertAndExtractMin (incorrect min value after second extraction)" << std::endl;
        exit(1);
    }
}

void testSize() {
    PriorityQueue<int> pq;
    if (pq.size() != 0) {
        std::cerr << "Test failed: testSize (incorrect size for empty queue)" << std::endl;
        exit(1);
    }

    pq.insert(10, 1);
    pq.insert(20, 2);
    if (pq.size() != 2) {
        std::cerr << "Test failed: testSize (incorrect size after insertions)" << std::endl;
        exit(1);
    }
}

int main() {
    testIsEmpty();
    testInsertAndExtractMin();
    testSize();

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}