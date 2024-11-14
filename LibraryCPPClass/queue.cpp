#include "queue.h"
#include "vector.h"
#include <stdexcept>

// Конструктор по умолчанию
Queue::Queue() : vector_(), front_(0), back_(0), size_(0) {
    vector_.resize(4); // Изначально задаём вместимость вектора
}

// Копирующий конструктор
Queue::Queue(const Queue &a) : vector_(a.vector_), front_(a.front_), back_(a.back_), size_(a.size_) {}

// Оператор присваивания
Queue &Queue::operator=(const Queue &a) {
    if (this != &a) {
        vector_ = a.vector_;
        front_ = a.front_;
        back_ = a.back_;
        size_ = a.size_;
    }
    return *this;
}

// Деструктор
Queue::~Queue() {}

// Вставка элемента в очередь
void Queue::insert(Data data) {
    if (size_ == vector_.size()) { // Увеличиваем массив, если он заполнен
        size_t new_capacity = vector_.size() * 2;
        Vector new_vector;
        new_vector.resize(new_capacity);
        for (size_t i = 0; i < size_; ++i) {
            new_vector.set(i, vector_.get((front_ + i) % vector_.size()));
        }
        front_ = 0;
        back_ = size_;
        vector_ = new_vector;
    }
    vector_.set(back_, data);
    back_ = (back_ + 1) % vector_.size();
    ++size_;
}

// Получение элемента из начала очереди
Data Queue::get() const {
    if (empty()) throw std::out_of_range("Queue is empty");
    return vector_.get(front_);
}

// Удаление элемента из начала очереди
void Queue::remove() {
    if (empty()) throw std::out_of_range("Queue is empty");
    front_ = (front_ + 1) % vector_.size();
    --size_;
}

// Проверка, пуста ли очередь
bool Queue::empty() const {
    return size_ == 0;
}
