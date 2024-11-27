#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* q;
    size_t nach;
    size_t kon;
    size_t size;
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->q = vector_create();
    vector_resize(queue->q, 1);
    queue->nach = 0;
    queue->kon = 0;
    queue->size = 0;
    return queue;
}

void queue_delete(Queue* queue)
{
    // TODO: free queue items
    vector_delete(queue->q);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (queue->size == vector_size(queue->q)) {
        Vector* new_vector = vector_create();
        vector_resize(new_vector, queue->size * 2);

        for (size_t i = 0; i < queue->size; i++) {
            vector_set(new_vector, i, vector_get(queue->q, (queue->nach + i) % vector_size(queue->q)));
        }

        vector_delete(queue->q);
        queue->q = new_vector;
        queue->nach = 0;
        queue->kon = queue->size;
    }

    vector_set(queue->q, queue->kon, data);
    queue->kon = (queue->kon + 1) % vector_size(queue->q);
    queue->size++;
}

Data queue_get(const Queue* queue)
{
    return vector_get(queue->q, queue->nach);
}

void queue_remove(Queue* queue)
{
    if (!queue_empty(queue)) {
        queue->nach = (queue->nach + 1) % vector_size(queue->q);
        queue->size--;
    }
}

bool queue_empty(const Queue* queue)
{
    return queue->size == 0;
}
