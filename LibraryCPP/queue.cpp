#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;

    Queue() {
        this->vector = vector_create();
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
    vector_resize(queue->vector, vector_size(queue->vector) + 1);
    return vector_set(queue->vector, vector_size(queue->vector) - 1, data);
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, 0);
}

void queue_remove(Queue *queue)
{
    if (queue_empty(queue)) throw "Queue is empty";
    else {
        Vector* temp_vector = vector_create();
        vector_resize(temp_vector, vector_size(queue->vector) - 1);
        for (int i = 1; i < vector_size(queue->vector); i++)
        {
            vector_set(temp_vector, i-1, vector_get(queue->vector, i));
        }
        vector_delete(queue->vector);
        queue->vector = temp_vector;
    }
}

bool queue_empty(const Queue *queue)
{
    if (vector_size(queue->vector) == 0) return true;
    else return false;
}
