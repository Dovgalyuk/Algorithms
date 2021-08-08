#ifndef QUEUE_H
#define QUEUE_H

template <typename Data> class Queue
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
    }

    // Retrieves first element from the queue
    Data get() const
    {
        return Data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return true;
    }

private:
    // private data should be here
};

#endif
