#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "list.h"
#include <stdexcept>
template <typename Data> class Queue
{
private:
    List<Data> l;
public:
    // Create empty queue
    Queue()
    {
    }

    // copy constructor
    Queue(const Queue &a): l(a.l)
    {
        // implement or disable this function
    }

    // assignment operator
    Queue &operator=(const Queue &a)
    {
        // implement or disable this function
        l=a.l;
        return *this;
    }

    // Deletes queue
    ~Queue()
    {
    }

    // Retrieves first element from the queue
    Data get() 
    {
        if (l.first() == nullptr)
        {
            throw std::out_of_range("Queue is empty");
        }
        return l.first()->f_data();
    }
    
    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if (l.first() == nullptr)
        {
            l.insert(data);
        }
        else
        {
            l.insert_after(l.first()->f_prev(), data);
        }
    }


    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        if (l.first() == nullptr)
        {
            throw std::out_of_range("Queue is empty");
        }
        l.erase_first();
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        // if ()
        // {
        //     return false;
        // }
        return l.first() == nullptr;
    }
    
};

#endif
