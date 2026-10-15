#include <cstddef>
#include "queue.h"
#include "vector.h"

struct Queue
{
	Vector* data;
	size_t head;
	size_t kolvo_el;
};

Queue* queue_create() {
	Queue* queue = new Queue;
	queue->data = vector_create();
	queue->head = 0;
	queue->kolvo_el = 0;
	return queue;
}

void queue_delete(Queue* queue) {
	if (queue == nullptr) {
		return;
	}
	vector_delete(queue->data);
	delete queue;
}

void queue_insert(Queue* queue, Data data) {
	if (queue == nullptr) {
		return;
	}

	size_t pamyat = vector_size(queue->data);

	if (queue->kolvo_el == pamyat) {
		size_t new_pamyat = (pamyat == 0) ? 1 : pamyat * 2;
		Vector* new_data = vector_create();
		vector_resize(new_data, new_pamyat);

		for (size_t i = 0; i < queue->kolvo_el; i++) {
			size_t stari_index = (queue->head + i) % pamyat;
			vector_set(new_data, i, vector_get(queue->data, stari_index));
		}

		vector_delete(queue->data);
		queue->data = new_data;

		queue->head = 0;
	}
	
	size_t tail = (queue->head + queue->kolvo_el) % vector_size(queue->data);
	vector_set(queue->data, tail, data);
	queue->kolvo_el++;
}

Data queue_get(const Queue* queue) {
	if (queue == nullptr || queue->kolvo_el == 0) {
		return (Data)0;
	}
	return vector_get(queue->data, queue->head);
}

void queue_remove(Queue* queue) {
	if (queue == nullptr || queue->kolvo_el == 0) {
		return;
	}
	queue->head = (queue->head + 1) % vector_size(queue->data);
	queue->kolvo_el--;
}

bool queue_empty(const Queue* queue) {
	if (queue == nullptr || queue->kolvo_el == 0) {
		return true;
	}
	return false;
}
