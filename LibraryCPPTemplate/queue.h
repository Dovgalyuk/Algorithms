#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include <stdexcept>

#include "list.h"

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue() = default;

    // Copy constructor
    Queue(const Queue& a) = default;

    // Assignment operator
    Queue& operator=(const Queue& a) = default;

    // Deletes queue
    ~Queue() = default;

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        m_items.insert_after(m_items.last(), data);
    }

    // Retrieves first element from the queue
    Data get() const
    {
        const typename List<Data>::Item* item = m_items.first();
        if (item == nullptr)
        {
            throw std::out_of_range("Queue is empty");
        }
        return item->data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        if (empty())
        {
            throw std::out_of_range("Queue is empty");
        }
        m_items.erase_first();
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return m_items.first() == nullptr;
    }

private:
    List<Data> m_items;
};

#endif