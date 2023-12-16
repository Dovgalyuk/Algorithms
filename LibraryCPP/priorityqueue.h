#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
template <typename T>
class PriorityQueue {
public:
    PriorityQueue();
    void insert(const T& item, int priority);
    T extractMin();
    bool isEmpty() const;
    size_t size() const;

private:
    void bubbleUp(int index);
    void bubbleDown(int index);
    int parent(int index) const;
    int leftChild(int index) const;
    int rightChild(int index) const;

    std::vector<std::pair<T, int>> heap;
};

#endif