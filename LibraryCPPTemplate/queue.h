#ifndef QUEUE_H
#define QUEUE_H

#include <vector.h>

template <typename Data> class Queue: private Vector<Data>
{
public:
    // Create empty queue
    Queue()
    {
    }

    // Deletes queue
    ~Queue()
    {
    }

    void sort() {
        size_t size = this->size();
        Data* new_data = new Data[size];
        for (int i = 0; i < size; ++i) {
            new_data[i] = this->data[(i + first) % size];
        }
        for (int i = 0; i < size; ++i) {
            this->data[i] = new_data[i];
        }
        first = 0;
        last = size - 1;
    }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if (length == this->size()) {
            if (first > 0) {
                sort();
            }
            this->resize(this->size() + 1);
        }
        last = ++last % this->size();
        this->data[last] = data;
        length++;
    }

    // Retrieves first element from the queue
    Data get() const
    {
        return this->data[first];
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        first = ++first % this->size();
        if (length > 0) {
            length--;
        }
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return !length;
    }

private:
    size_t first = 0;
    size_t last = 0;
    size_t length = 0;
};

#endif
