#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

class Queue {
private:
    List* list;

public:
    Queue();
    ~Queue();
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void insert(Data data);
    Data get() const;
    void remove();
    bool empty() const;
};

Queue* queue_create();
void queue_delete(Queue* queue);
void queue_insert(Queue* queue, Data data);
Data queue_get(const Queue* queue);
void queue_remove(Queue* queue);
bool queue_empty(const Queue* queue);

#endif
