#include "queue.h"
#include <stdexcept>

Queue::Queue():m_data(new Vector())
{
}

Queue::~Queue()
{
    delete m_data;
}

void Queue::insert(Data data)
{
    if (offset*2 >= m_data->size()) // reallocate
    {
        auto newData = new Vector();
        size_t newSize = m_data->size()-offset + 1;
        newData->resize(newSize);
        for (size_t i = offset; i < m_data->size(); i++)
        {
            newData->set(i-offset, m_data->get(i));
        }
        newData->set(newData->size() - 1 , data);//last element is new
        delete m_data;
        m_data = newData;
        offset = 0;
    }
    else
    {
        m_data->resize(m_data->size() + 1);
        m_data->set(m_data->size() - 1, data);
    }
}

Data Queue::get() const
{
    if(offset >= m_data->size()){
        throw std::runtime_error("Incorrect offset");
    }
    auto data = m_data->get(offset);
    return data;
}

void Queue::remove()
{
    if(offset >= m_data->size()){
        throw std::logic_error("remove() called on empty queue");
    }
    offset++;
}

bool Queue::empty() const
{
    return m_data->size() == offset;
}
