#include "queue.h"
#include "vector.h"

struct Queue
{
    size_t head;
    size_t count;
    Vector *vector;

    Queue() :head(0), count(0) , vector(vector_create()){}

    ~Queue() {
        vector_delete(vector);
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
    if (!queue) return;

    if (queue->count == vector_size(queue->vector)) {
        Vector *temp = vector_create();
        vector_resize(temp, vector_size(queue->vector) == 0 ? 2 : vector_size(queue->vector) * 2);

        for (size_t i = 0; i < queue->count; i++) {
            vector_set(temp, i, vector_get(queue->vector, (queue->head + i) % vector_size(queue->vector)));
        }

        vector_delete(queue->vector);
        queue->vector = temp;
        queue->head = 0;
    }

    vector_set(queue->vector, (queue->head + queue->count) % vector_size(queue->vector), data);

    queue->count++;
}

Data queue_get(const Queue *queue)
{
    if (!queue_empty(queue)) return vector_get(queue->vector, queue->head);
    return  -1;
}

void queue_remove(Queue *queue)
{
    if (!queue_empty(queue)) {
        queue->head = (queue->head + 1) % vector_size(queue->vector);
        queue->count--;
    }
}

bool queue_empty(const Queue *queue)
{
    return !queue || queue->count == 0;
}
