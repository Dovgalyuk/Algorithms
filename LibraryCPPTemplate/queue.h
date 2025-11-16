#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include <stdexcept>

#include "concepts.h"
#include "list.h"

template <std::copyable Data>
class Queue
{
public:
    // Create empty queue
    Queue() = default;

    // copy constructor
    Queue(const Queue &a) : data_(a.data_) {
        tail_ = findTail(data_);
    }

    Queue(Queue &&a) noexcept : data_(std::move(a.data_)), tail_(a.tail_) { a.tail_ = nullptr; }

    // assignment operator
    Queue &operator=(const Queue &a)
    {
        if (this != &a) {
            data_ = a.data_;
            tail_ = findTail(data_);
        }
        return *this;
    }

    Queue &operator=(Queue &&a) noexcept {
        if (this != &a) {
            data_ = std::move(a.data_);
            tail_ = a.tail_;
            a.tail_ = nullptr;
        }
        return *this;
    }

    // Deletes queue
    ~Queue() = default;

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if (empty()) {
            data_.insert(data);
            tail_ = data_.first();
        } else {
            tail_ = data_.insert_after(tail_, data);
        }
    }

    // Retrieves first element from the queue
    Data& get()
    {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return data_.front();
    }

    const Data& get() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return data_.front();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        data_.erase_first();
        if (data_.empty()) {
            tail_ = nullptr;
        }
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return data_.empty();
    }

private:
    // private data should be here

    static List<Data>::Item* findTail(List<Data>& lst) {
        auto* item = lst.first();
        if (!item) { return nullptr; }
        while (item->next() != nullptr) {
            item = item->next();
        }
        return item;
    }

    List<Data> data_;
    List<Data>::Item* tail_ = nullptr;
};

#endif
