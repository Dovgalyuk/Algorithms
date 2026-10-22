
#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename Data>
class List
{
public:
    class Item
    {
        friend class List<Data>;

    private:
        Data value;
        Item* nextItem;
        Item* prevItem;

        Item(const Data& data)
            : value(data),
              nextItem(nullptr),
              prevItem(nullptr)
        {
        }

    public:
        Item* next()
        {
            return nextItem;
        }

        Item* prev()
        {
            return prevItem;
        }

        Data data() const
        {
            return value;
        }
    };

private:
    Item* head = nullptr;
    Item* tail = nullptr;
    std::size_t count = 0;

    void swap(List& other) noexcept
    {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(count, other.count);
    }

public:
    List() = default;

    // Создание независимой копии списка
    List(const List& other)
    {
        try
        {
            for (Item* p = other.head;
                 p != nullptr;
                 p = p->nextItem)
            {
                insert_after(tail, p->value);
            }
        }
        catch (...)
        {
            clear();
            throw;
        }
    }

    // Присваивание другого списка
    List& operator=(const List& other)
    {
        if (this != &other)
        {
            List copy(other);
            swap(copy);
        }

        return *this;
    }

    // Освобождение памяти
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

    // Первый элемент
    Item* first()
    {
        return head;
    }

    // Последний элемент
    Item* last()
    {
        return tail;
    }

    // Добавление в начало
    Item* insert(Data data)
    {
        Item* node = new Item(data);

        node->nextItem = head;

        if (head != nullptr)
        {
            head->prevItem = node;
        }
        else
        {
            tail = node;
        }

        head = node;
        ++count;

        return node;
    }

    // Добавление после указанного элемента
    Item* insert_after(Item* item, Data data)
    {
        if (item == nullptr)
        {
            return insert(data);
        }

        Item* node = new Item(data);

        node->prevItem = item;
        node->nextItem = item->nextItem;

        if (item->nextItem != nullptr)
        {
            item->nextItem->prevItem = node;
        }
        else
        {
            tail = node;
        }

        item->nextItem = node;
        ++count;

        return node;
    }

    // Удаление первого элемента
    Item* erase_first()
    {
        if (head == nullptr)
        {
            return nullptr;
        }

        Item* old = head;
        head = head->nextItem;

        if (head != nullptr)
        {
            head->prevItem = nullptr;
        }
        else
        {
            tail = nullptr;
        }

        delete old;
        --count;

        return head;
    }

    // Удаление элемента после указанного
    Item* erase_next(Item* item)
    {
        if (item == nullptr)
        {
            return erase_first();
        }

        Item* target = item->nextItem;

        if (target == nullptr)
        {
            return nullptr;
        }

        Item* next = target->nextItem;

        item->nextItem = next;

        if (next != nullptr)
        {
            next->prevItem = item;
        }
        else
        {
            tail = item;
        }

        delete target;
        --count;

        return next;
    }

    // Очистка списка
    void clear()
    {
        while (head != nullptr)
        {
            erase_first();
        }
    }
};

#endif
