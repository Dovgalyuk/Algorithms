#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "list.h"

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue()
        : m_list()
    { }

    // copy constructor
    Queue(const Queue &a)
        : m_list(a.m_list)
    { }

    // assignment operator
    Queue &operator=(const Queue &a)
    {
        if (this != &a) {
            m_list = a.m_list;
        }
        
        return *this;
    }

    // Deletes queue
    ~Queue()
    { }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        m_list.insert_after(m_list.last(), data);
    }

    // Retrieves first element from the queue
    Data get() const
    {
        if (m_list.first() == nullptr) {
            throw std::runtime_error("Queue is empty");
        }
        return m_list.first()->data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        m_list.erase_first();
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return m_list.first() == nullptr;
    }

private:
    // private data should be here
    List<Data> m_list;
};

#endif
