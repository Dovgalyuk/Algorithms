#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>  // for size_t


typedef char Data;  
struct QueueNode
{
    Data data;
    QueueNode *next;
};

struct Queue
{
    QueueNode *front;
    QueueNode *rear;
};

Queue *queue_create();
void queue_delete(Queue *queue);
void queue_insert(Queue *queue, Data data);
Data queue_get(const Queue *queue);
void queue_remove(Queue *queue);
bool queue_empty(const Queue *queue);

#endif 