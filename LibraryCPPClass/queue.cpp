#include "queue.h"

Queue::Queue()
{
    vector = new Vector();
    head = 0;
    count = 0;
}

Queue::Queue(const Queue &a)
{
    vector = new Vector(*a.vector);
    head = a.head;
    count = a.count;
}

Queue &Queue::operator=(const Queue &a)
{
    if (this != &a)
    {
        *vector = *a.vector;
        head = a.head;
        count = a.count;
    }
    return *this;
}

Queue::~Queue()
{
    delete vector;
}

void Queue::insert(Data data)
{
    if (vector->size() == 0)
    {
        vector->resize(4);
    }
    else if (count == vector->size())
    {
        size_t old_size = vector->size();
        size_t new_size = old_size * 2;
        Vector *new_vector = new Vector();
        new_vector->resize(new_size);
        for (size_t i = 0; i < count; ++i)
        {
            new_vector->set(i, vector->get((head + i) % old_size));
        }
        delete vector;
        vector = new_vector;
        head = 0;
    }

    size_t index = (head + count) % vector->size();
    vector->set(index, data);
    count++;
}

Data Queue::get() const
{
    if (count == 0)
    {
        return Data();
    }
    return vector->get(head);
}

void Queue::remove()
{
    if (count > 0)
    {
        head = (head + 1) % vector->size();
        count--;
    }
}

bool Queue::empty() const
{
    return count == 0;
}
