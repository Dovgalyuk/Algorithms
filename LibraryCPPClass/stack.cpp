#include "stack.h"
#include <stdexcept>

// Конструктор по умолчанию
Stack::Stack() : list_() {}

// Копирующий конструктор
Stack::Stack(const Stack &a) : list_(a.list_) {}

// Оператор присваивания
Stack &Stack::operator=(const Stack &a) {
    if (this != &a) {
        list_ = a.list_; // Убеждаемся, что не присваиваем самому себе
    }
    return *this;
}

// Деструктор — автоматически удалит элементы списка
Stack::~Stack() {}

// Метод добавления элемента на вершину стека
void Stack::push(Data data) {
    list_.insert(data); // вставляем элемент в начало списка
}

// Метод для получения элемента с вершины стека
Data Stack::get() const {
    if (empty()) {
        throw std::out_of_range("Stack is empty"); // выбрасываем исключение, если стек пуст
    }
    return list_.first()->data();
}

// Метод для удаления элемента с вершины стека
void Stack::pop() {
    if (empty()) {
        throw std::out_of_range("Stack is empty"); // выбрасываем исключение, если стек пуст
    }
    list_.erase_first();
}
