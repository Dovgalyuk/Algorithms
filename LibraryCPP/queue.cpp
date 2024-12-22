#include "queue.h"
#include "vector.h"
#include <stdexcept> // Для использования std::runtime_error

// Определение структуры Queue с использованием динамического вектора для хранения данных
struct Queue {
    Vector* vector; // Динамический вектор для данных очереди
    size_t front;   // Индекс начала очереди
    size_t size;    // Количество элементов в очереди
};

// Создание новой очереди
Queue* queue_create() {
    Queue* queue = new Queue;
    queue->vector = vector_create(); // Создаем вектор
    vector_resize(queue->vector, 1);  // Начальный размер вектора
    queue->front = 0;                 // Устанавливаем индекс начала очереди
    queue->size = 0;                  // Изначально очередь пуста
    return queue;
}

// Удаление очереди и освобождение памяти
void queue_delete(Queue* queue) {
    vector_delete(queue->vector); // Удаляем внутренний вектор
    delete queue;                 // Удаляем структуру очереди
}

// Добавление элемента в очередь
void queue_insert(Queue* queue, Data data) {
    // Если очередь заполнена, увеличиваем размер вектора
    if (queue->size == vector_size(queue->vector)) {
        size_t new_size = vector_size(queue->vector) * 2 + 1; // Увеличиваем размер в 2 раза + 1
        Vector* new_vector = vector_create();
        vector_resize(new_vector, new_size);

        // Переносим элементы из старого вектора в новый
        for (size_t i = 0; i < queue->size; i++) {
            vector_set(new_vector, i, vector_get(queue->vector, (queue->front + i) % vector_size(queue->vector)));
        }

        vector_delete(queue->vector); // Удаляем старый вектор
        queue->vector = new_vector;  // Привязываем новый
        queue->front = 0;            // Обновляем индекс начала
    }

    // Вычисляем индекс для вставки (конец очереди)
    size_t rear = (queue->front + queue->size) % vector_size(queue->vector);
    vector_set(queue->vector, rear, data); // Добавляем элемент
    queue->size++;                         // Увеличиваем размер очереди
}

// Получение элемента из начала очереди без удаления
Data queue_get(const Queue* queue) {
    if (queue_empty(queue)) { // Если очередь пуста, генерируем исключение
        throw std::runtime_error("Queue is empty");
    }
    return vector_get(queue->vector, queue->front); // Возвращаем первый элемент
}

// Удаление элемента из начала очереди
void queue_remove(Queue* queue) {
    if (queue_empty(queue)) { // Если очередь пуста, генерируем исключение
        throw std::runtime_error("Queue is empty");
    }
    // Сдвигаем начало очереди
    queue->front = (queue->front + 1) % vector_size(queue->vector);
    queue->size--; // Уменьшаем размер очереди
}

// Проверка, пуста ли очередь
bool queue_empty(const Queue* queue) {
    return queue->size == 0; // Возвращаем true, если очередь пуста
}
