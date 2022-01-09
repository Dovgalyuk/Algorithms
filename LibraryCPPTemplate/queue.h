#ifndef QUEUE_H
#define QUEUE_H

#include <vector.h>

template <typename Data> class Queue: private Vector<Data>
{
public:
    // Создать пустую очередь
    Queue()
    {
    }

    // Удаляет очередь
    ~Queue()
    {
    }

    // Включает новый элемент в очередь
    // В среднем должно быть O(1)
    void insert(Data data)
    {
        if (amount == this->size()) { // если вектор заполн то увелич на 1 размер
            if (first > 0) {
                sort(); // восст послед 1 стан 1вым
            }
            this->resize(this->size() + 1); // увел размер на 1
        }
        last++;
        last %= this->size(); // чтоб не выход за пред массива
        this->data[last] = data;
        amount++; // увел кол-во
    }

    // Извлекает первый элемент из очереди
    Data get() const
    {
        return this->data[first];
    }

    // Удаляет первый элемент из очереди
    // В среднем должно быть O(1)
    void remove()
    {
        first++;
        first %= this->size();
        if (amount > 0) {
            amount--; // кол-во
        }
    }

    // Возвращает true, если очередь пуста
    bool empty() const
    {
        return !amount;
    }

private:
    size_t first = 0;
    size_t last = 0;
    size_t amount = 0;

    void sort() { // сортировка кольцевым буфером
        size_t size = this->size();
        Data* new_data = new Data[size];
        for (int i = 0; i < size; ++i) {
            new_data[i] = this->data[(i + first) % size];
        }
        delete[] this->data;
        this->data = new_data;
        last -= first;
        last += size;
        last %= size;
        first = 0;
    }
};

#endif
