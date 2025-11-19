#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#include <utility>

template <typename Data> class List {
public:
    class Item {
    public:
        Item* next() { return m_next; }
        const Item* next() const { return m_next; }

        Item* prev() { return m_prev; }
        const Item* prev() const { return m_prev; }

        Data& data() { return m_data; }
        const Data& data() const { return m_data; }
    private:
        explicit Item(const Data& d) : m_data(d), m_prev(nullptr), m_next(nullptr) {}

        Data  m_data;
        Item* m_prev;
        Item* m_next;

        friend class List<Data>;
    };

    // Creates new list
    List() : m_head(nullptr) {}

    // copy constructor
    List(const List& a) : m_head(nullptr) {
        Item* last = nullptr;
        for (const Item* p = a.m_head; p; p = p->m_next)
            last = insert_after(last, p->m_data);
    }

    // assignment operator
    List& operator=(const List& a) {
        if (this == &a)
            return *this;

        List tmp(a);
        std::swap(m_head, tmp.m_head);
        return *this;
    }

    // Destroys the list and frees the memory
    ~List() {
        while (m_head)
            erase_first();
    }

    // Retrieves the first item from the list
    Item* first() { return m_head; }
    const Item* first() const { return m_head; }

    // Inserts new list item into the beginning
    Item* insert(const Data& data) {
        Item* node = new Item(data);
        node->m_next = m_head;

        if (m_head)
            m_head->m_prev = node;

        m_head = node;
        return node;
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item* insert_after(Item* item, const Data& data) {
        if (!item)
            return insert(data);

        Item* node = new Item(data);
        node->m_prev = item;
        node->m_next = item->m_next;

        if (item->m_next)
            item->m_next->m_prev = node;

        item->m_next = node;
        return node;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item* erase_first() {
        if (!m_head)
            return nullptr;

        Item* rem = m_head;
        Item* nxt = rem->m_next;

        if (nxt)
            nxt->m_prev = nullptr;

        delete rem;
        m_head = nxt;
        return m_head;
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item* erase_next(Item* item) {
        if (!item)
            return erase_first();

        Item* rem = item->m_next;

        if (!rem)
            return nullptr;

        Item* after = rem->m_next;
        item->m_next = after;

        if (after)
            after->m_prev = item;

        delete rem;
        return after;
    }

    Item* erase_after(Item* item) {
        return erase_next(item);
    }
private:
    Item* m_head;
};

#endif