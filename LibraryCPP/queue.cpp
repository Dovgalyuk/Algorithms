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
    // TODO: free queue items
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{    
    size_t size = vector_size(queue->vector); // Получаем текущий размер вектора, который используется для хранения элементов очереди.
        
    if (queue_empty(queue)) { // Если очередь пуста, инициализируем индексы начала и конца очереди нулём.
        queue->rear = 0;
        queue->head = 0;
    }
    
    else if (queue->rear % static_cast<int>(size) == queue->head) { // Если очередь полностью заполнена (т.е. хвост очереди находится в позиции головы), то необходимо увеличить размер вектора, чтобы можно было добавить новый элемент.
        
        Vector* buff = vector_create(); // Создаем новый вектор с удвоенным размером.
        vector_resize(buff, size * 2);

        int counter = 0;
                
        for (size_t i = queue->head; i < size; i++) { // Перекопируем элементы из старой очереди в новую, начиная с головы.
            vector_set(buff, counter, vector_get(queue->vector, i));
            counter++;
        }
        
        for (int i = 0; i < queue->rear; i++) { // Перекопируем оставшиеся элементы, которые находятся перед головой. Чтобы не было не заполненных элементов в векторе
            vector_set(buff, counter, vector_get(queue->vector, i));
            counter++;
        }
        
        vector_delete(queue->vector); // Удаляем старый вектор и заменяем его новым.
        queue->vector = buff;
        
        queue->head = 0; // Сбрасываем индексы начала и конца очереди.
        queue->rear = static_cast<int>(size);

        size = vector_size(queue->vector); // Обновляем размер, так как вектор был расширен.
    }
    
    auto rear = queue->rear % size; // Вычисляем индекс для вставки нового элемента в векторе, который используется как кольцевой буфер.
    
    vector_set(queue->vector, rear, data); // Вставляем новый элемент в очередь по вычисленному индексу.
    
    queue->rear = rear + 1; // Обновляем индекс "хвоста" очереди, чтобы указывать на следующую позицию для вставки.
}

Data queue_get(const Queue* queue)
{
    if (!queue_empty(queue)) {
        Data value = vector_get(queue->vector, queue->head);
        return value;
    }
    return Data();
}

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
            queue->head = head % size; //Устанавливается новый индекс головы, учитывая размер очереди.            
        }
    }
}

bool queue_empty(const Queue* queue)
{
    return (queue->rear == -1 && queue->head == -1);
}
