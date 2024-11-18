#include "queue.h"

Queue::Queue()
{
}

Queue::~Queue()
{
}

void Queue::insert(Data data)
{
    m_data.resize(m_data.size() + 1);
    m_data.set(m_data.size() - 1, data);
}

Data Queue::get() const
{
    return m_data.get(0);
}

void Queue::remove()
{
    m_data.erase_first();
}

bool Queue::empty() const
{
    return m_data.size() == 0;
}
