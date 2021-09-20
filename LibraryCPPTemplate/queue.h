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

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if (last == offset) {
            size_t new_size = this->size() + 1;
            last = this->size();
            if (offset > 0) {
                Data* new_data = new Data[new_size];
                this->data_copy(new_data, this->size() - offset, offset);
                this->data_copy(new_data, offset, 0, this->size() - offset);
                delete[] this->data;
                this->data = new_data;
                this->length = new_size;
                offset = 0;
            } else {
                this->resize(new_size);
            }
        }
        this->set(last, data);
        last++;
        last %= this->size();
        offset %= this->size();
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
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return (this->size() - offset) <= 0;
    }

private:
    size_t offset = 0;
    size_t last = 0;
};

#endif
