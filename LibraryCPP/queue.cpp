#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;
    
    size_t head;
    size_t tail;

    Queue() {
        this->vector = vector_create();
        this->head = 0;
        this->tail = 0;
    }

    ~Queue() {
        vector_delete(this->vector);
    }
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue_empty(queue)) {
        vector_resize(queue->vector, 30);
        vector_set(queue->vector, queue->head, data);
        queue->tail++;
    }
    else if (queue->head == queue->tail) {
        vector_set(queue->vector, 0, queue_get(queue));
        queue->head = 0;
        queue->tail = 1;
        queue_insert(queue, data);
    }
    else if (queue->tail == vector_size(queue->vector) - 1) {
        vector_resize(queue->vector, vector_size(queue->vector) * 2);
        vector_set(queue->vector, queue->tail, data);
        queue->tail++;
    } 
    else {
        vector_set(queue->vector, queue->tail, data);
        queue->tail++;
    }
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue_empty(queue)) throw "Queue is empty";
    else if (queue->head+1 == queue->tail) {
        vector_set(queue->vector, queue->head, 0);
        queue->tail = 0;
        queue->head = 0;
    }
    else {
        vector_set(queue->vector, queue->head, 0);
        queue->head++;
    }
}

bool queue_empty(const Queue *queue)
{
    if (queue->head == queue->tail && queue->head == 0) return true;
    else return false;
}
