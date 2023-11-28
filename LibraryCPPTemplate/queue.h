#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "vector.h"

const std::size_t queue_prebuffer_ratio = vector_prebuffer_ratio;

template <typename Data>
class Queue
{
public:
    // Create empty queue
    Queue() : mVector(), mBegin(0) {}

    // copy constructor
    Queue(const Queue &a)
    {
        // implement or disable this function
        mVector = a.mVector;
        mBegin = a.mBegin;
    }

    // assignment operator
    Queue &operator=(Queue &a)
    {
        // implement or disable this function
        mVector = a.mVector;
        mBegin = a.mBegin;
        return *this;
    }

    // Deletes queue
    // ~Queue() {}

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        mVector.resize(mVector.size() + 1);
        mVector[mVector.size() - 1] = data;
    }

    // Retrieves first element from the queue
    Data get() const
    {
        return mVector[mBegin];
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        std::size_t buffer_size = (std::size_t)(mVector.size() * (queue_prebuffer_ratio - 1));
        mVector[mBegin] = 0;
        mBegin++;
        if (buffer_size - mBegin == 0)
        {
            shift_left(buffer_size);
            mBegin = 0;
        }
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return mVector.size() - mBegin == 0;
    }

private:
    // private data should be here
    Vector<Data> mVector;
    std::size_t mBegin;

    void shift_left(std::size_t count)
    {
        Vector<Data> result;
        result.resize(mVector.size() - count);
        for (std::size_t i = count; i < mVector.size(); i++)
            std::swap(mVector[i], result[i - count]);
        mVector = result;
    }
};

#endif
