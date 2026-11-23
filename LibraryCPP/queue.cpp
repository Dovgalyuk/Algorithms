#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *elements;
    size_t first_position;
    size_t element_count;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->elements = vector_create();

    vector_resize(queue->elements, 4);

    queue->first_position = 0;
    queue->element_count = 0;

    return queue;
}

void queue_delete(Queue *queue)
{
    if (queue == nullptr)
    {
        return;
    }

    vector_delete(queue->elements);
    delete queue;
}

void queue_insert(Queue *queue, Data value)
{
    size_t array_capacity = vector_size(queue->elements);

    if (queue->element_count == array_capacity)
    {
        Vector *new_elements = vector_create();
        vector_resize(new_elements, array_capacity * 2);

        for (size_t i = 0; i < queue->element_count; i = i + 1)
        {
            size_t old_position = queue->first_position + i;

            if (old_position >= array_capacity)
            {
                old_position = old_position - array_capacity;
            }

            Data old_value = vector_get(queue->elements, old_position);
            vector_set(new_elements, i, old_value);
        }

        vector_delete(queue->elements);

        queue->elements = new_elements;
        queue->first_position = 0;

        array_capacity = array_capacity * 2;
    }

    size_t last_position = queue->first_position + queue->element_count;

    if (last_position >= array_capacity)
    {
        last_position = last_position - array_capacity;
    }

    vector_set(queue->elements, last_position, value);
    queue->element_count = queue->element_count + 1;
}

Data queue_get(const Queue *queue)
{
    if (queue->element_count == 0)
    {
        return 0;
    }

    return vector_get(queue->elements, queue->first_position);
}

void queue_remove(Queue *queue)
{
    if (queue->element_count == 0)
    {
        return;
    }

    queue->first_position = queue->first_position + 1;

    size_t array_capacity = vector_size(queue->elements);

    if (queue->first_position >= array_capacity)
    {
        queue->first_position = 0;
    }

    queue->element_count = queue->element_count - 1;

    if (queue->element_count == 0)
    {
        queue->first_position = 0;
    }
}

bool queue_empty(const Queue *queue)
{
    if (queue->element_count == 0)
    {
        return true;
    }

    return false;
}
