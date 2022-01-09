#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue(): _queue(new List<Data>())
    {
    }

    // Deletes queue
    ~Queue()
    {

    }

    // Добавляет новый элемент в очередь
    // Should be O(1) on average
    void insert(Data data)
    {
        _queue->insert_end(data);
    }

    // Извлекает первый элемент из очереди
    Data get() const
    {
        return _queue->first()->data();
    }

    // Удаляет первый элемент из очереди
    // Should be O(1) on average
    void remove()
    {
        _queue->erase(_queue->first());
    }

    // Возвращает true, если очередь пуста
    bool empty() const
    {
        return _queue->empty();
    }

private:
    // private data should be here
    List<Data>* _queue;
};

#endif
