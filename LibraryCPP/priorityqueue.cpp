#include "priorityqueue.h"

template <typename T>
PriorityQueue<T>::PriorityQueue() {}

template <typename T>
void PriorityQueue<T>::insert(const T& item, int priority) {
    heap.push_back({ item, priority });
    bubbleUp(heap.size() - 1);
}

template <typename T>
T PriorityQueue<T>::extractMin() {
    if (isEmpty()) {
        throw std::runtime_error("Attempt to extract from empty queue");
    }
    T minItem = heap.front().first;
    heap[0] = heap.back();
    heap.pop_back();
    bubbleDown(0);
    return minItem;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const {
    return heap.empty();
}

template <typename T>
size_t PriorityQueue<T>::size() const {
    return heap.size();
}

template <typename T>
void PriorityQueue<T>::bubbleUp(int index) {
    while (index > 0 && heap[parent(index)].second > heap[index].second) {
        std::swap(heap[index], heap[parent(index)]);
        index = parent(index);
    }
}

template <typename T>
void PriorityQueue<T>::bubbleDown(int index) {
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

template <typename T>
int PriorityQueue<T>::parent(int index) const {
    return (index - 1) / 2;
}

template <typename T>
int PriorityQueue<T>::leftChild(int index) const {
    return 2 * index + 1;
}

template <typename T>
int PriorityQueue<T>::rightChild(int index) const {
    return 2 * index + 2;
}
