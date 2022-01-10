#ifndef QUEUE_H
#define QUEUE_H
#include <vector.h>


template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue()
    {
        vector = new Vector<Data>();
    }

    // Deletes queue
    ~Queue()
    {
        delete vector;
    }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if (tail + 1 == head){
            auto* new_vector = new Vector<Data>();
            new_vector->resize(vector->size() + 1);
            for (size_t i = head; i < vector->size(); ++i) {
                new_vector->set(i - head, vector->get(i));
            }
            for (size_t i = 0; i < tail; ++i) {
                new_vector->set(i + head, vector->get(i));
            }
            head = 0;
            tail = new_vector->size();
            new_vector->set(tail - 1, data);
            delete vector;
            vector = new_vector;
        }  else {
            if (tail != vector->size()) {
                vector->set(tail, data);
                tail++;
            } else {
                if (head != 0) {
                    tail = 0;
                    vector->set(tail, data);
                } else {
                    vector->resize(vector->size() + 1);
                    vector->set(tail, data);
                    ++tail;
                }
            }

        }
    }

    // Retrieves first element from the queue
    Data get() const
    {
        return vector->get(head);
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        if (head < vector->size() - 1) {
            head++;
        } else {
            if (head < tail)
                head++;
            else head = 0;
        }
    }

// Returns true if the queue is empty
bool empty() const
{
    return tail == head;
}

private:
// private data should be here
    Vector<Data> *vector;
    size_t head = 0;
    size_t tail = 0;
};

#endif