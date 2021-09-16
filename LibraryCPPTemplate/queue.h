#ifndef QUEUE_H
#define QUEUE_H

#include <vector.h>

template <typename Data> class Queue: private Vector<Data>
{
public:
    // Create empty queue
    Queue(): offset(0)
    {
    }

    // Deletes queue
    ~Queue()
    {
        delete this;
    }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        size_t index = this->size();
        this->resize(index + 1);
        this->set(index, data);
    }

    // Retrieves first element from the queue
    Data get() const
    {
        return this->data[offset];
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        offset++;
        if (offset > max_offset) {
            size_t new_size = offset + this->size() - 1;
            if (new_size < 0)
                return;
            Data* new_data = new Data[new_size];
            this->data_copy(new_data, new_size, offset);
            this->resize(new_size);
            delete[] this->data;
            this->data = new_data;
            offset = 0;
        }
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return (this->size() - offset) == 0;
    }

private:
    size_t offset;
    const size_t max_offset = 10;
};

#endif
