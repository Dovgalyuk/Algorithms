#ifndef LIST_H
#define LIST_H

#include <stdexcept>
#include <cstddef>

template <typename Data>
class List
{
private:
    struct Node
    {
        Data value;
        Node* next;

        Node(const Data& value)
        {
            this->value = value;
            next = nullptr;
        }
    };

    Node* head;
    std::size_t count;

public:
    List()
    {
        head = nullptr;
        count = 0;
    }

    ~List()
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

    // Добавить в начало
    void pushFront(const Data& value)
    {
        Node* newNode = new Node(value);

        newNode->next = head;
        head = newNode;

        count++;
    }

    // Добавить в конец
    void pushBack(const Data& value)
    {
        Node* newNode = new Node(value);

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node* current = head;

            while (current->next != nullptr)
            {
                current = current->next;
            }

            current->next = newNode;
        }

        count++;
    }

    // Получить первый элемент
    Data& front()
    {
        if (empty())
        {
            throw std::runtime_error("Список пуст");
        }

        return head->value;
    }

    // Получить последний элемент
    Data& back()
    {
        if (empty())
        {
            throw std::runtime_error("Список пуст");
        }

        Node* current = head;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        return current->value;
    }

    const Data& front() const
    {
        if (empty())
        {
            throw std::runtime_error("Список пуст");
        }

        return head->value;
    }

    const Data& back() const
    {
        if (empty())
        {
            throw std::runtime_error("Список пуст");
        }

        Node* current = head;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        return current->value;
    }

    // Удалить первый элемент
    void popFront()
    {
        if (empty())
        {
            throw std::runtime_error("Список пуст");
        }

        Node* temp = head;
        head = head->next;

        delete temp;
        count--;
    }

    // Удалить последний элемент
    void popBack()
    {
        if (empty())
        {
            throw std::runtime_error("Список пуст");
        }

        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            Node* current = head;

            while (current->next->next != nullptr)
            {
                current = current->next;
            }

            delete current->next;
            current->next = nullptr;
        }

        count--;
    }

    // Перевернуть список
    void reverse()
    {
        Node* previous = nullptr;
        Node* current = head;

        while (current != nullptr)
        {
            Node* next = current->next;

            current->next = previous;
            previous = current;
            current = next;
        }

        head = previous;
    }

    void clear()
    {
        while (!empty())
        {
            popFront();
        }
    }

    Data& at(std::size_t index)
    {
        if (index >= count)
        {
            throw std::out_of_range("Индекс за пределами списка");
        }

        Node* current = head;

        for (std::size_t i = 0; i < index; i++)
        {
            current = current->next;
        }

        return current->value;
    }

    const Data& at(std::size_t index) const
    {
        if (index >= count)
        {
            throw std::out_of_range("Индекс за пределами списка");
        }

        Node* current = head;

        for (std::size_t i = 0; i < index; i++)
        {
            current = current->next;
        }

        return current->value;
    }
};

#endif