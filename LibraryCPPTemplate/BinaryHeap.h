#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#define TEMPLATE_H template<typename Data, bool(*comparator)(const Data&, const Data&)>
#define CLASS BinaryHeap<Data, comparator>

#include "vector.h"

TEMPLATE_H
class BinaryHeap {
public:
    // Constructor with comparator
    BinaryHeap() {}

    // Insert an element into the heap
    void push(const Data& value);

    // Remove an element from the heap
    Data pop();

    // Get an element with the highest priority
    Data top();

    // Check if the heap is empty
    bool is_empty();

    // Get the size of the heap
    size_t size();

private:
    // Array for elements
    Vector<Data> arr;

    // Helper function to restore heap property after pop
    void apply_rules(size_t index);
};

TEMPLATE_H
void CLASS::push(const Data& value) {
    arr.push(value);
    size_t i = arr.size() - 1;
    size_t parent = (i - 1) / 2;

    while (i > 0 && comparator(arr[i], arr[parent])) {
        std::swap(arr[parent], arr[i]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

TEMPLATE_H
Data CLASS::pop() {
    if (arr.size() == 0)
        return Data();

    Data temp = arr[0];
    arr[0] = arr[arr.size() - 1];
    arr.erase(arr.size() - 1);
    apply_rules(0);
    return temp;
}

TEMPLATE_H
void CLASS::apply_rules(size_t index) {
    size_t left, right, smallest = index;

    while (smallest != index) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        size_t smallest = index;

        if (left < arr.size() && comparator(arr[left], arr[smallest])) {
            smallest = left;
        }
        if (right < arr.size() && comparator(arr[right], arr[smallest])) {
            smallest = right;
        }

        std::swap(arr[index], arr[smallest]);
    }
}

TEMPLATE_H
Data CLASS::top() {
    if (arr.size() == 0)
        return Data();
    return arr[0];
}

TEMPLATE_H
bool CLASS::is_empty() {
    return arr.size() == 0;
}

TEMPLATE_H
size_t CLASS::size() {
    return arr.size();
}

#endif