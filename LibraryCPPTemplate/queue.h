#ifndef QUEUE_H
#define QUEUE_H

#include "vector.h"
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
            if (end >= start && start != 0) {
                end = 0;
                _vector->set(end,data);
                ++end;
            }
            else
            {
                if (start == 0) {
                    _vector->resize(_vector->size() + 1);
                    _vector->set(end, data);
                    ++end;
                } else {
                    auto* new_vector = new Vector<Data>();
                    new_vector->resize(_vector->size() + 1);
                    for (size_t i = start; i < _vector->size(); ++i) {
                        new_vector->set(i - start, _vector->get(i));
                    }
                    for (size_t i = 0; i < end; ++i) {
                        new_vector->set(i + start, _vector->get(i));
                    }
                    start = 0;
                    end = new_vector->size();
                    new_vector->set(end - 1, data);
                    delete _vector;
                    _vector = new_vector;
                }
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
        if (start < end) {
            start++;
            if (start == _vector->size()) {
                start = 0;
            }
            if (end == _vector->size()) {
                end = 0;
            }
        } else {
            if (_vector->size() - 1> start) {
                start++;
            } else {
                start = 0;
            }
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
