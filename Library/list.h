
#ifndef LIBRARY_STACK_H
#define LIBRARY_STACK_H

#include <cstddef>
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

        Node(const Data& value, Node* nextNode = nullptr)
            : data(value), next(nextNode) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    std::size_t count = 0;

public:
    Stack() = default;

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    ~Stack()
    {
        clear();
    }

    bool empty() const
    {
        return head == nullptr;
    }

    std::size_t size() const
    {
        return count;
    }

    // Добавление наверх
    void push(Data data)
    {
        Node* node = new Node(data, head);
        head = node;

        if (tail == nullptr)
            tail = node;

        ++count;
    }

    // Получение верхнего элемента
    Data get() const
    {
        if (empty())
            throw std::out_of_range("Stack is empty");

        return head->data;
    }

    // Удаление верхнего элемента
    void pop()
    {
        if (empty())
            throw std::out_of_range("Stack is empty");

        Node* old = head;
        head = head->next;
        delete old;

        --count;

        if (head == nullptr)
            tail = nullptr;
    }

    // Получение нижнего элемента
    Data& bottom()
    {
        if (empty())
            throw std::out_of_range("Stack is empty");

        return tail->data;
    }

    const Data& bottom() const
    {
        if (empty())
            throw std::out_of_range("Stack is empty");

        return tail->data;
    }

    // Добавление снизу
    void pushBottom(const Data& data)
    {
        Node* node = new Node(data);

        if (tail != nullptr)
            tail->next = node;
        else
            head = node;

        tail = node;
        ++count;
    }

    // Удаление нижнего элемента
    void popBottom()
    {
        if (empty())
            throw std::out_of_range("Stack is empty");

        if (head == tail)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node* current = head;

            while (current->next != tail)
                current = current->next;

            delete tail;
            tail = current;
            tail->next = nullptr;
        }

        --count;
    }

    // Доступ по индексу от вершины
    Data& at(std::size_t index)
    {
        if (index >= count)
            throw std::out_of_range("Invalid index");

        Node* current = head;

        for (std::size_t i = 0; i < index; ++i)
            current = current->next;

        return current->data;
    }

    const Data& at(std::size_t index) const
    {
        if (index >= count)
            throw std::out_of_range("Invalid index");

        const Node* current = head;

        for (std::size_t i = 0; i < index; ++i)
            current = current->next;

        return current->data;
    }

    // Переворот стека
    void reverse()
    {
        Node* previous = nullptr;
        Node* current = head;

        tail = head;

        while (current != nullptr)
        {
            Node* next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }

        head = previous;
    }

    // Очистка
    void clear()
    {
        while (!empty())
            pop();
    }
};

#endif
