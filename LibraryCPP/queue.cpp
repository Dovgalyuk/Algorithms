#include "queue.h"
#include "vector.h"
struct Queue
{
    Vector* data;

	size_t head;
    size_t tail;
    size_t count;
};

Queue *queue_create()
{
	Queue* queue = new Queue;

	queue->data = vector_create();
	vector_resize(queue->data, 4);

	queue->head = 0;
    queue->tail = 0;
	queue->count = 0;

    return queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
	vector_delete(queue->data);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->count == vector_size(queue->data)) {

		size_t starii_size = vector_size(queue->data);
        vector_resize(queue->data, starii_size * 2);
    }

	vector_set(queue->data, queue->tail, data);
	queue->tail = (queue->tail + 1) % vector_size(queue->data);
	queue->count++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->data, queue->head);
}

void queue_remove(Queue *queue)
{
	if (queue->count > 0) {
		queue->head = (queue->head + 1) % vector_size(queue->data);
		queue->count--;
	}
}

bool queue_empty(const Queue *queue)
{
    return queue->count==0;
}
