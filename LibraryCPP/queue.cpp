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
    else if (queue->tail == vector_size(queue->vector) - 1 && queue->head == 0) {
        vector_resize(queue->vector, vector_size(queue->vector) * 2);
        vector_set(queue->vector, queue->tail, data);
        queue->tail++;
    }
    else if (queue->tail + 1 == queue->head) {
        Vector* temp_queue = vector_create();
        vector_resize(temp_queue, vector_size(queue->vector) * 2);

        int indexTempQueue = 0;
        for (int i = queue->head; i < vector_size(queue->vector); i++)
        {
            vector_set(temp_queue, indexTempQueue, vector_get(queue->vector, i));
            indexTempQueue++;
        }
        for (int i = 0; i < queue->tail; i++)
        {
            vector_set(temp_queue, indexTempQueue, vector_get(queue->vector, i));
            indexTempQueue++;
        }

        vector_delete(queue->vector);
        queue->vector = temp_queue;

        queue->head = 0;
        queue->tail = indexTempQueue;
    }
    else if (queue->tail == vector_size(queue->vector) - 1 && queue->head >= 0) {
        vector_set(queue->vector, queue->tail, data);
        queue->tail = 0;
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
    else if (queue->head == vector_size(queue->vector) - 1) {
        vector_set(queue->vector, queue->head, 0);
        queue->head = 0;
    }
    else {
        vector_set(queue->vector, queue->head, 0);
        queue->head++;
    }
}

bool queue_empty(const Queue *queue)
{
    if (queue->head == queue->tail) return true;
    else return false;
}
