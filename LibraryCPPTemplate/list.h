#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#include <cstddef>
#include <utility>

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return next_item; }
        Item *next() const { return next_item; }
        Item *prev() { return prev_item; }
        Item *prev() const { return prev_item; }
        Data &data() { return value; }
        const Data &data() const { return value; }
    private:
        explicit Item(Data item) : value(item), next_item(nullptr), prev_item(nullptr) {}
        Data value;
        Item *next_item;
        Item *prev_item;
        friend class List<Data>;
    };

    // Creates new list
    List() : head(nullptr), tail(nullptr), count(0) {}

    // copy constructor
    List(const List &a) : List() { for (Item *i = a.head; i; i = i->next()) insert_after(tail, i->data()); }

    // assignment operator
    List &operator=(const List &a) { if (this != &a) { List copy(a); swap(copy); } return *this; }

    // Destroys the list and frees the memory
    ~List() { clear(); }

    // Retrieves the first item from the list
    Item *first()
    {
        return head;
    }
    Item *first() const { return head; }

    // Retrieves the last item of the list
    Item *last()
    {
        return tail;
    }
    Item *last() const { return tail; }

    // Inserts new list item into the beginning
    Item *insert(Data data) { return insert_after(nullptr, data); }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data)
    {
        Item *created = new Item(data);
        if (!item) {
            created->next_item = head;
            if (head) head->prev_item = created; else tail = created;
            head = created;
        } else {
            created->prev_item = item;
            created->next_item = item->next_item;
            if (item->next_item) item->next_item->prev_item = created; else tail = created;
            item->next_item = created;
        }
        count++;
        return created;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        if (!head) return nullptr;
        Item *next_item = head->next_item;
        delete head;
        head = next_item;
        if (head) head->prev_item = nullptr; else tail = nullptr;
        count--;
        return head;
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        Item *victim = item ? item->next_item : head;
        if (!victim) return nullptr;
        Item *next_item = victim->next_item;
        if (item) item->next_item = next_item; else head = next_item;
        if (next_item) next_item->prev_item = item; else tail = item;
        delete victim;
        count--;
        return next_item;
    }

    size_t size() const { return count; }

private:
    void clear() { while (head) erase_first(); }
    void swap(List &a) { std::swap(head, a.head); std::swap(tail, a.tail); std::swap(count, a.count); }
    Item *head;
    Item *tail;
    size_t count;
};

#endif
