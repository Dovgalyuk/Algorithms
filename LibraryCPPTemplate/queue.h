#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "list.h"

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue()
    {
        mTail = nullptr;
        // mList создается сам
    }

    // copy constructor
    Queue(const Queue &a)
    {
        // implement or disable this function
        mList = a.mList;
        updateTail();
    }

    // assignment operator
    Queue &operator=(const Queue &a)
    {
        // implement or disable this function
        if (this != &a) {
            mList = a.mList;
            updateTail();
        }
        return *this;
    }

    // Deletes queue
    ~Queue()
    {
        // Деструктор листа вызывается сам
    }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if (mList.first() == nullptr) {
            mList.insert(data);
            mTail = mList.first();
        }
        else mTail = mList.insert_after(mTail, data); 
    }

    // Retrieves first element from the queue
    Data get() const
    {
        if (mList.first() != nullptr) return mList.first()->data();

        return Data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        if (mList.first() != nullptr) {
            mList.erase_first();
            if (mList.first() == nullptr) mTail = nullptr;
        }
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return mList.first() == nullptr;
    }

private:
    List<Data> mList;
    typename List<Data>::Item *mTail;

    void updateTail() {
        if (mList.first() == nullptr) mTail = nullptr;
        else {
            typename List<Data>::Item *current = mList.first();

            while (current->next() != nullptr) current = current->next();
            
            mTail = current;
        }
    }
};

#endif