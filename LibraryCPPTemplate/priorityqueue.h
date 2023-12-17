#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
template <typename T>
class PriorityQueue {
public:
    PriorityQueue() = default;
    ~PriorityQueue() = default;
    void insert(const T& item, int priority) {
        heap.push_back({ item, priority });
        bubbleUp((int)heap.size() - 1);
    }
    T extractMin() {
        if (isEmpty()) {
            throw std::runtime_error("Attempt to extract from empty queue");
        }
        T minItem = heap.front().first;
        heap[0] = heap.back();
        heap.pop_back();
        bubbleDown(0);
        return minItem;
    }
    bool isEmpty() const {
        return heap.empty();
    }
    size_t size() const {
        return heap.size();
    }

private:
    void bubbleUp(int index) {
        while (index > 0 && heap[parent(index)].second > heap[index].second) {
            std::swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }
    void bubbleDown(int index) {
        int smallest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < heap.size() && heap[left].second < heap[smallest].second) {
            smallest = left;
        }
        if (right < heap.size() && heap[right].second < heap[smallest].second) {
            smallest = right;
        }
        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            bubbleDown(smallest);
        }
    }
    int parent(int index) const {
        return (index - 1) / 2;
    }
    int leftChild(int index) const {
        return 2 * index + 1;
    }
    int rightChild(int index) const {
        return 2 * index + 2;
    }

    std::vector<std::pair<T, int>> heap;
};

#endif