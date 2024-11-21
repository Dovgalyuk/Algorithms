#include "queue.h"
#include "vector.h"
#include <cstdlib>

struct Queue {
	Vector* vector;
	size_t front;
	size_t back;
	size_t size;
};

Queue* queue_create() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (queue != nullptr) {
		queue->vector = vector_create();
		vector_resize(queue->vector, 1);
		queue->front = queue->back = queue->size = 0;
	}
	return queue;
}

void queue_delete(Queue* queue) {
	vector_delete(queue->vector);
	free(queue);
}

void queue_insert(Queue* queue, Data data) {
	if (queue->size == vector_size(queue->vector)) {
		vector_resize(queue->vector, vector_size(queue->vector) * 2);
	}
	queue->back = (queue->back + 1) % vector_size(queue->vector);
	vector_set(queue->vector, queue->back, data);
	queue->size++;
}

Data queue_get(const Queue* queue) {
	if (queue_empty(queue) || queue == nullptr) {
		return (Data)0;
	}
	return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue* queue) {
	if (!queue_empty(queue)) {
		for (size_t i = queue->front; i < queue->back; i++) {
			vector_set(queue->vector, i, vector_get(queue->vector, (i + 1) % vector_size(queue->vector)));
		}
		queue->front = (queue->front + 1) % vector_size(queue->vector);
		queue->size--;
	}
}

bool queue_empty(const Queue* queue) {
	if (queue != nullptr && queue->size == 0) {
		return true;
	}
	return false;
}
