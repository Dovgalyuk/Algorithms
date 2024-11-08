#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
  Vector* vec;
};

Queue *queue_create()
{
  Queue *queue = new Queue;
  queue->vec = vector_create();
  return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vec);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    size_t size = vector_size(queue->vec);
    vector_resize(queue->vec, size + 1);
    vector_set(queue->vec, size, data);
}

Data queue_get(const Queue *queue)
{
    if (vector_size(queue->vec) == 0)
        throw std::out_of_range("The queue is empty");
    return vector_get(queue->vec, 0);

}

void queue_remove(Queue *queue)
{
    if (vector_size(queue->vec) == 0)
        throw std::out_of_range("The queue is empty");
    size_t size = vector_size(queue->vec);
    for (size_t i = 0; i < size - 1; i++) {
        vector_set(queue->vec, i, vector_get(queue->vec, i + 1));
    }
    vector_resize(queue->vec, size - 1);
}

bool queue_empty(const Queue *queue)
{
    return vector_size(queue->vec) == 0;
}
