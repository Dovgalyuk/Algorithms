#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "vector.h"
#include <utility>

template <typename T>
class PriorityQueue
{
public:
    PriorityQueue() {}

    bool empty() const { return data_.size() == 0; }
    size_t size() const { return data_.size(); }
    T top() const { return data_.get(0); }

    void push(const T& value)
    {
        data_.resize(data_.size() + 1);
        data_.set(data_.size() - 1, value);
        sift_up(data_.size() - 1);
    }

    void pop()
    {
        if (data_.size() == 0) return;
        if (data_.size() == 1) { data_.resize(0); return; }

        data_.set(0, data_.get(data_.size() - 1));
        data_.resize(data_.size() - 1);
        sift_down(0);
    }

private:
    Vector<T> data_;

    void sift_up(size_t index)
    {
        while (index > 0)
        {
            size_t parent = (index - 1) / 2;
            if (data_.get(index) < data_.get(parent))
            {
                T temp = data_.get(index);
                data_.set(index, data_.get(parent));
                data_.set(parent, temp);
                index = parent;
            }
            else break;
        }
    }

    void sift_down(size_t index)
    {
        size_t size = data_.size();
        while (true)
        {
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;
            size_t smallest = index;

            if (left < size && data_.get(left) < data_.get(smallest)) smallest = left;
            if (right < size && data_.get(right) < data_.get(smallest)) smallest = right;

            if (smallest != index)
            {
                T temp = data_.get(index);
                data_.set(index, data_.get(smallest));
                data_.set(smallest, temp);
                index = smallest;
            }
            else break;
        }
    }
};

#endif