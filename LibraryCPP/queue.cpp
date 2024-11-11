#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
    Vector* vec;
    size_t size;
    size_t front;
    size_t back;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->vec = vector_create();
    vector_resize(queue->vec, 1);
    queue->size = 0;
    queue->front = 0;
    queue->back = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vec);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->size == vector_size((queue->vec))) {
        size_t new_size = queue->size * 2;
        Vector *new_vec = vector_create();
        vector_resize(new_vec, new_size);

        //Копируем элементы
        for (size_t i = 0; i < queue->size; ++i) {
            vector_set(new_vec, i, vector_get(queue->vec, (queue->front + i) % vector_size(queue->vec)));
        }
        vector_delete(queue->vec);
        queue->vec = new_vec;
        queue->front = 0;
        queue->back = queue->size;
    }
    vector_set(queue->vec, queue->back, data);
    queue->back = (queue->back + 1) % vector_size(queue->vec);
    queue->size++;
}

Data queue_get(const Queue *queue)
{
    if (queue->size == 0)
        throw std::out_of_range("The queue is empty");
    return vector_get(queue->vec, queue->front);
}

void queue_remove(Queue *queue)
{
    if (queue->size == 0)
        throw std::out_of_range("The queue is empty");
    queue->front = (queue->front + 1) % vector_size(queue->vec);
    queue->size--;
}

bool queue_empty(const Queue *queue)
{
    return queue->size == 0;
}