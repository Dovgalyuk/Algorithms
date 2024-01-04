#include "queue.h"
#include "vector.h"

template <typename T>
class Queue
{
public:
    Queue() : vec(Vector()), head(0), tail(0) {}

    Queue(const Queue& a) : vec(a.vec), head(a.head), tail(a.tail) {}

    Queue& operator=(const Queue& a)
    {
        if (this != &a)
        {
            vec = a.vec;
            head = a.head;
            tail = a.tail;
        }
        return *this;
    }

    ~Queue() {}

    void insert(Data data)
    {
        if (vec.size() == 0)
            vec.resize(1);
        else if (tail == vec.size())
            vec.resize(vec.size() * 2);
        vec.set(tail++, data);
    }

    Data get() const
    {
        if (empty())
            throw std::out_of_range("Queue is empty");
        return vec.get(head);
    }

    void remove()
    {
        if (empty())
            throw std::out_of_range("Queue is empty");
        head++;
    }

    bool empty() const
    {
        return head == tail;
    }

private:
    Vector vec;
    size_t head;
    size_t tail;
};
