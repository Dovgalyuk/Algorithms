#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "vector.h"
#include <stdexcept>

template <typename Data>
class Queue {
public:
    Queue() {}

    // Copy constructor
    Queue(const Queue& other) : data_(other.data_) {}

    // Move constructor
    Queue(Queue&& other) noexcept : data_(std::move(other.data_)) {}

    ~Queue() {}

    void insert(const Data& data) {
        data_.resize(data_.size() + 1); // Увеличиваем размер на 1
        data_.set(data_.size() - 1, data); // Устанавливаем значение в последний элемент
    }

    Data get() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return data_.get(0); // Получаем первый элемент
    }

    void remove() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        data_.erase(0); // Удаляем первый элемент
    }

    bool empty() const {
        return data_.size() == 0; // Проверяем, пустая ли очередь
    }

private:
    Vector<Data> data_; // Используем вектор для хранения данных
};

#endif
