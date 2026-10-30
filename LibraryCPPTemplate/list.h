#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#include <cstddef>
#include <utility>

// Односвязный список с доступом к первому и последнему элементам.
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

        explicit Item(const Data& data) : value(data), nextItem(nullptr) {}

    public:
        Item* next() const { return nextItem; }
        Data data() const { return value; }
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

    // Глубокое копирование: элементы копии независимы от исходного списка.
    List(const List& other)
    {
        try
        {
            for (const Item* item = other.head; item != nullptr; item = item->nextItem)
                insert_after(tail, item->value);
        }
        catch (...)
        {
            clear();
            throw;
        }
    }

    List(List&& other) noexcept
        : head(other.head), tail(other.tail), count(other.count)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }

    List& operator=(const List& other)
    {
        if (this != &other)
        {
            List copy(other);
            swap(copy);
        }
        return *this;
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            head = other.head;
            tail = other.tail;
            count = other.count;
            other.head = nullptr;
            other.tail = nullptr;
            other.count = 0;
        }
        return *this;
    }

    ~List() { clear(); }

    bool empty() const { return head == nullptr; }
    std::size_t size() const { return count; }
    Item* first() const { return head; }
    Item* last() const { return tail; }

    // Добавляет новый элемент в начало списка за O(1).
    Item* insert(Data data)
    {
        Item* node = new Item(data);
        node->nextItem = head;
        head = node;
        if (tail == nullptr)
            tail = node;
        ++count;
        return node;
    }

    // Вставляет после item; при item == nullptr добавляет в начало.
    Item* insert_after(Item* item, Data data)
    {
        if (item == nullptr)
            return insert(data);

        Item* node = new Item(data);
        node->nextItem = item->nextItem;
        item->nextItem = node;
        if (tail == item)
            tail = node;
        ++count;
        return node;
    }

    // Удаляет первый элемент и возвращает новый первый элемент.
    Item* erase_first()
    {
        if (head == nullptr)
            return nullptr;

        Item* old = head;
        head = head->nextItem;
        if (head == nullptr)
            tail = nullptr;
        delete old;
        --count;
        return head;
    }

    // Удаляет элемент после item за O(1); nullptr означает удалить первый.
    Item* erase_next(Item* item)
    {
        if (item == nullptr)
            return erase_first();

        Item* target = item->nextItem;
        if (target == nullptr)
            return nullptr;

        item->nextItem = target->nextItem;
        if (tail == target)
            tail = item;
        delete target;
        --count;
        return item->nextItem;
    }

    void clear()
    {
        while (head != nullptr)
            erase_first();
    }
};

#endif
