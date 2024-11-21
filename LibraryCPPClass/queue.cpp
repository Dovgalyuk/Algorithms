#include "queue.h"
#include <stdexcept>

Queue::Queue()
{
}

Queue::~Queue()
{
    delete m_data;
}

void Queue::resizeAndAlign()
{
    m_data->resize(m_data->size() + 1);
    if (m_head == 0) // no need to align
    {
        return;
    }
    for (size_t i = m_data->size() - 1; i > m_head; i--)
    {
        m_data->set(i, m_data->get(i - 1));
    }
    m_head++;
}
void Queue::insert(Data data)
{
    if (m_size + 1 > m_data->size())
    {
        resizeAndAlign();
    }
    auto lastElIndex = (m_head + m_size) % m_data->size();
    m_data->set(lastElIndex, data);
    m_size++;
}

Data Queue::get() const
{
    return m_data->get(m_head);
}

void Queue::remove()
{
    if (empty())
    {
        throw std::logic_error("remove() called on empty queue");
    }
    m_size--;
    m_head = (m_head + 1) % m_data->size();
}

bool Queue::empty() const
{
    return m_size == 0;
}
