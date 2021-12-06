#ifndef QUEUE_H
#define QUEUE_H

#include <vector.h>
#include <cstddef>

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue(): _vector(new Vector<Data>())
    {
    }

    // Deletes queue
    ~Queue()
    {
        delete _vector;
    }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if(end != _vector->size())
        {
            _vector->set(end,data);
            end++;
        }
        else
        {
            if (start != 0)
            {
                for (int i = 0; i < end - start; ++i) {
                    _vector->set(i, _vector->get(start + i));
                }
                end -= start;
                start = 0;
                insert(data);
            } else {
                _vector->resize(end + 1);
                insert(data);
            }
        }
    }


    // Retrieves first element from the queue
    Data get() const
    {
        return _vector->get(start);
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        if(!empty())
        {
            start++;
        }
        //return 0;
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        //return true;
        return end == start;
    }

private:
    // private data should be here
    Vector<Data> *_vector;
    size_t start = 0;
    size_t end = 0;
};

#endif