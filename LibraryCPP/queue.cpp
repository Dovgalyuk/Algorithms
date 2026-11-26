#include "queue.h"
#include "vector.h"

// Очередь на основе кольцевого буфера
struct Queue
{
    Vector *vector;
    size_t head = 0;
    size_t count = 0;
};

Queue *queue_create()
{
    Queue *q = new Queue;
    q->vector = vector_create();
    return q;
}

void queue_delete(Queue *queue)
{
    if (queue)
    {
        vector_delete(queue->vector);
        delete queue;
    }
}

void queue_insert(Queue *queue, Data data)
{
    size_t cap = vector_size(queue->vector);

    // Если буфер полон — расширяем его в 2 раза
    if (queue->count == cap)
    {
        size_t new_cap = (cap == 0) ? 4 : cap * 2;
        Vector *new_vec = vector_create();
        vector_resize(new_vec, new_cap);

        // Переносим элементы по порядку от 0 до count - 1
        for (size_t i = 0; i < queue->count; ++i)
            vector_set(new_vec, i, vector_get(queue->vector, (queue->head + i) % cap));

        vector_delete(queue->vector);
        queue->vector = new_vec;
        queue->head = 0;
        cap = new_cap;
    }

    // Записываем в позицию (head + count) % cap
    vector_set(queue->vector, (queue->head + queue->count) % cap, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue->count > 0)
    {
        queue->head = (queue->head + 1) % vector_size(queue->vector);
        queue->count--;
    }
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}
