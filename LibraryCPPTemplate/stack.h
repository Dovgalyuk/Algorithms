#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include <cstddef>      // для nullptr
#include <stdexcept>    // для std::out_of_range

template <typename Data>
class Stack {
public:
    // Конструктор по умолчанию
    Stack() : _top(nullptr) {}

    // Конструктор копирования (глубокое копирование)
    Stack(const Stack &other) : _top(nullptr) {
        if (!other._top) return;

        // Копируем данные во временный стек в обратном порядке
        Stack<Data> temp;
        for (Node* cur = other._top; cur; cur = cur->next)
            temp.push(cur->data);

        // Переносим обратно в this (в нужном порядке)
        while (!temp.empty()) {
            push(temp.get());
            temp.pop();
        }
    }

    // Оператор присваивания
    Stack &operator=(const Stack &other) {
        if (this != &other) {
            clear();
            Stack<Data> temp;
            for (Node* cur = other._top; cur; cur = cur->next)
                temp.push(cur->data);
            while (!temp.empty()) {
                push(temp.get());
                temp.pop();
            }
        }
        return *this;
    }

    // Деструктор
    ~Stack() {
        clear();
    }

    // Добавить элемент на вершину стека
    void push(Data data) {
        Node* new_node = new Node(data, _top);
        _top = new_node;
    }

    // Вернуть верхний элемент (не удаляя)
    Data get() const {
        if (!_top)
            throw std::out_of_range("Stack is empty");
        return _top->data;
    }

    // Удалить верхний элемент
    void pop() {
        if (!_top) return;
        Node* temp = _top;
        _top = _top->next;
        delete temp;
    }

    // Проверить, пуст ли стек
    bool empty() const {
        return _top == nullptr;
    }

private:
    struct Node {
        Data data;
        Node* next;
        Node(Data d, Node* n = nullptr) : data(d), next(n) {}
    };

    Node* _top;

    // Очистить стек
    void clear() {
        while (_top) {
            pop();
        }
    }
};

#endif
