
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

        Node(const Data& value, Node* nextNode = nullptr)
            : data(value), next(nextNode)
        {
        }
    };

    Node* head = nullptr;

    // Удаление всех элементов
    void clear()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

public:
    // Создание пустого стека
    Stack() = default;

    // Конструктор копирования
    Stack(const Stack& other) : head(nullptr)
    {
        Node** current = &head;

        try
        {
            for (const Node* p = other.head;
                 p != nullptr;
                 p = p->next)
            {
                *current = new Node(p->data);
                current = &((*current)->next);
            }
        }
        catch (...)
        {
            clear();
            throw;
        }
    }

    // Оператор присваивания
    Stack& operator=(const Stack& other)
    {
        if (this != &other)
        {
            Stack temp(other);
            std::swap(head, temp.head);
        }

        return *this;
    }

    // Деструктор
    ~Stack()
    {
        clear();
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
