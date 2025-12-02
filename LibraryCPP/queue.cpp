#include "queue.h"
#include "vector.h"
struct Queue
{
	Vector* data; //указатель на вектор для хранения элементов очереди

	size_t head;// индекс головы очереди
    size_t count; // колличестно элементов в очереди 
};

Queue *queue_create()
{
	Queue* queue = new Queue;// создаётся структура очереди

	queue->data = vector_create(); // создаётся вектор для хранения элементов очереди	
	vector_resize(queue->data, 4); // начальный размер вектора 4 элемента

	queue->head = 0;// инициализация головы очереди, индекс начинается с 0
	queue->count = 0; // инициализация количества элементов в очереди, изначально 0

	return queue;// возвращаем указатель на созданную очередь
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
	vector_delete(queue->data);// освобождаем память вектора
	delete queue;// освобождаем память структуры очереди
}

void queue_insert(Queue *queue, Data data)//добавление элементов
{
	if (queue->count == vector_size(queue->data)) {// если количество элементов равно размеру вектора
	
		size_t starii_size = vector_size(queue->data);// сохраняем старый размер вектора
		vector_resize(queue->data, starii_size * 2);// увеличиваем размер вектора вдвое
    }

	size_t tail = (queue->head + queue->count) % vector_size(queue->data);
	// вычисляем индекс хвоста очереди с учётом цикличности
	vector_set(queue->data, tail, data); // добавляем элемент в хвост очереди
	queue->count++; // увеличиваем количество элементов в очереди
}

Data queue_get(const Queue *queue)
{
	return vector_get(queue->data, queue->head); // возвращаем элемент в голове очереди
}

void queue_remove(Queue* queue) // удаление элемента из очереди
{
	if (queue->count > 0) { // если в очереди есть элементы
		queue->head = (queue->head + 1) % vector_size(queue->data);
		// обновляем индекс головы очереди с учётом цикличности
		queue->count--; // уменьшаем количество элементов в очереди
	}
}

bool queue_empty(const Queue *queue)
{
    return queue->count==0;
}
