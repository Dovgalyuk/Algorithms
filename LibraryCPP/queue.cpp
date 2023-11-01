#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;
    ptrdiff_t head;
    ptrdiff_t rear;

    Queue() {
        vector = vector_create();
        vector_resize(vector, 2);
        head = -1;
        rear = -1;
    }
    ~Queue() {
        vector_delete(vector);
    }
};

Queue* queue_create()
{
    return new Queue;
}

void queue_delete(Queue* queue)
{
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    // Получаем текущий размер вектора, который используется для хранения элементов очереди.
    size_t size = vector_size(queue->vector);

    // Если очередь пуста, инициализируем индексы начала и конца очереди нулём.
    if (queue_empty(queue)) {
        queue->rear = 0;
        queue->head = 0;
    }
    // Если очередь полностью заполнена (т.е. хвост очереди находится в позиции головы),
    // то необходимо увеличить размер вектора, чтобы можно было добавить новый элемент.
    else if (queue->rear % static_cast<int>(size) == queue->head) {
        // Создаем новый вектор с удвоенным размером.
        Vector* buff = vector_create();
        vector_resize(buff, size * 2);

        int counter = 0;

        // Перекопируем элементы из старой очереди в новую, начиная с головы.
        for (size_t i = queue->head; i < size; i++) {
            vector_set(buff, counter, vector_get(queue->vector, i));
            counter++;
        }
        // Перекопируем оставшиеся элементы, которые находятся перед головой.
        for (int i = 0; i < queue->rear; i++) {
            vector_set(buff, counter, vector_get(queue->vector, i));
            counter++;
        }
        // Удаляем старый вектор и заменяем его новым.
        vector_delete(queue->vector);
        queue->vector = buff;
        // Сбрасываем индексы начала и конца очереди.
        queue->head = 0;
        queue->rear = static_cast<int>(size);

        // Обновляем размер, так как вектор был расширен.
        size = vector_size(queue->vector);
    }

    // Вычисляем индекс для вставки нового элемента в векторе, который используется как кольцевой буфер.
    auto rear = queue->rear % size;
    // Вставляем новый элемент в очередь по вычисленному индексу.
    vector_set(queue->vector, rear, data);
    // Обновляем индекс "хвоста" очереди, чтобы указывать на следующую позицию для вставки.
    queue->rear = rear + 1;
}

Data queue_get(const Queue* queue)
{
    if (!queue_empty(queue)) {
        Data value = vector_get(queue->vector, queue->head);
        return value;
    }
    return Data();
}

//удаляет элемент из начала очереди
void queue_remove(Queue* queue)
{
    size_t size = vector_size(queue->vector);
    auto head = queue->head;

    if (!queue_empty(queue)) {
        head++;

        if (queue->rear == head) {
            queue->head = -1;
            queue->rear = -1;
        }
        else {
            queue->head = head % size;
            //Устанавливается новый индекс головы, учитывая размер очереди.
        }
    }
}

bool queue_empty(const Queue* queue)
{
    return (queue->rear == -1 && queue->head == -1);
}