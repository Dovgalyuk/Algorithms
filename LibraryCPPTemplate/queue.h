#ifndef QUEUE_H
#define QUEUE_H
#include <vector.h>

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue()
    {
        vector =  new Vector<Data>();
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
        vector->resize(vector->size() + 1);
        vector->set(vector->size() - 1, data);
    }

    // Retrieves first element from the queue
    Data get() const
    {
        return vector->get(0);
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        for (size_t i = 0; i < (vector->size() - 1); i++)
        {
            vector->set(i, vector->get(i+1));
        }
        vector->resize(vector->size() - 1);
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return vector->size() <= 0;
    }

private:
    // private data should be here
    Vector<Data> *vector;
};

#endif
