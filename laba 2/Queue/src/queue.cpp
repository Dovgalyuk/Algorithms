#include <stdlib.h>
#include "queue.h"
#include "vector.h"

struct Queue {
	Vector *vector;
	size_t head;
	size_t tail;
};
// �������� ������ �������
Queue *queue_create() {
	Queue *queue = new Queue;
	queue->vector = vector_create();
	queue->head = 0;
	queue->tail = 0;
	vector_resize(queue->vector, 1);
	return queue;
}

// �������� �������
void queue_delete(Queue *queue) {
	vector_delete(queue->vector);
	delete queue;
}

// ��������� �������� � �������
void queue_insert(Queue *queue, int data) {
	if (queue->tail + 1 == queue->head) {
		size_t oldsize = vector_size(queue->vector);
		vector_resize(queue->vector, oldsize * 2);
		for (size_t i = oldsize - 1; i >= queue->head; i--) {
			vector_set(queue->vector, oldsize + i,
					vector_get(queue->vector, i));
		}
		queue->head = queue->head + oldsize;
	} else if (queue->head == 0 && queue->tail == vector_size(queue->vector)) {
		size_t oldsize = vector_size(queue->vector);
		vector_resize(queue->vector, oldsize * 2);
	}
	vector_set(queue->vector, queue->tail, data);
	queue->tail++;
	if (queue->head != 0 && queue->tail == vector_size(queue->vector)) {
		queue->tail = 0;
	}
}

// ��������� ������� �������� �������
int queue_get(Queue *queue) {
	if (queue->head == queue->tail) {
		return 0;
	}
	return vector_get(queue->vector, queue->head);
}

// �������� ������� �������� �� �������
void queue_remove(Queue *queue) {
	if (queue->head == queue->tail) {
		return;
	}
	queue->head++;
	if (queue->head == vector_size(queue->vector)
			&& queue->head != queue->tail) {
		queue->head = 0;
	}
}

// �������� ������� �� ������� ���������
bool queue_empty(Queue *queue) {
	return queue->head == queue->tail;
}
