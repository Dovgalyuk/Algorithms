
#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include <stdexcept>
#include <utility>

template <typename Data>
class Stack
{
private:
    struct Node
    {
        Data data;
        Node* next;

        Node(const Data& value, Node* nextNode)
            : data(value), next(nextNode) {}
    };

    Node* head = nullptr;

public:
    // Создание пустого стека
    Stack() = default;

    // Запрещаем копирование
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    // Удаление всех элементов
    ~Stack()
    {
        while (!empty())
        {
            pop();
        }
    }

    // Добавление элемента на вершину
    void push(Data data)
    {
        head = new Node(data, head);
    }

    // Получение верхнего элемента
    Data get() const
    {
        if (empty())
        {
            throw std::out_of_range("Stack is empty");
        }

        return head->data;
    }

    // Удаление верхнего элемента
    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Stack is empty");
        }

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Проверка пустоты
    bool empty() const
    {
        return head == nullptr;
    }
};

#endif
