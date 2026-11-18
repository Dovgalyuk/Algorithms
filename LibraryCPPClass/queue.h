#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include "vector.h"

// Change it to desired type
typedef int Data;

class Queue
{
public:
    // Create empty queue
    Queue();

    // copy constructor
    Queue(const Queue &a);

    // assignment operator
    Queue &operator=(const Queue &a);

    // Deletes queue
    ~Queue();

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data);

    // Retrieves first element from the queue
    Data get() const;

    // Removes first element from the queue
    // Should be O(1) on average
    void remove();

    // Returns true if the queue is empty
    bool empty() const;

private:
    // увеличивает буфер в два раза, когда в нём не осталось места
    void grow();

    // кольцевой буфер: после последней ячейки идёт снова нулевая.
    // Размер вектора - это вместимость очереди.
    Vector buffer_;
    size_t head_; // индекс первого элемента очереди
    size_t count_; // сколько элементов сейчас в очереди
};

#endif
