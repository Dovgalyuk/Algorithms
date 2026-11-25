#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item* next() { return m_next->m_is_sentinel ? nullptr : m_next; }
        Item* prev() { return m_prev->m_is_sentinel ? nullptr : m_prev; }
        Data data() const { return m_data; }

    private:
        friend class List<Data>;

        explicit Item(const Data& data, bool is_sentinel = false)
            : m_data(data), m_next(this), m_prev(this),
            m_is_sentinel(is_sentinel)
        {
        }

        Data m_data;
        Item* m_next;
        Item* m_prev;
        bool m_is_sentinel;
    };

    // Creates new list
    List() : m_sentinel(Data{}, true)
    {
    }

    // copy constructor
    List(const List& a) : List()
    {
        copy_from(a);
    }

    // assignment operator
    List& operator=(const List& a)
    {
        if (this != &a)
        {
            clear();
            copy_from(a);
        }
        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        clear();
    }

    // Retrieves the first item from the list
    Item* first()
    {
        return m_sentinel.next();
    }

    const Item* first() const
    {
        return m_sentinel.m_next == &m_sentinel
            ? nullptr : m_sentinel.m_next;
    }

    // Retrieves the last item of the list
    Item* last()
    {
        return m_sentinel.prev();
    }

    // Inserts new list item into the beginning
    Item* insert(Data data)
    {
        return insert_after(nullptr, data);
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item* insert_after(Item* item, Data data)
    {
        Item* prev = (item == nullptr) ? &m_sentinel : item;
        Item* next = prev->m_next;
        Item* node = new Item(data);

        node->m_prev = prev;
        node->m_next = next;
        prev->m_next = node;
        next->m_prev = node;

        return node;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item* erase_first()
    {
        return erase_next(nullptr);
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item* erase_next(Item* item)
    {
        Item* prev = (item == nullptr) ? &m_sentinel : item;
        Item* target = prev->m_next;

        if (target == &m_sentinel)
        {
            return nullptr;
        }

        Item* next = target->m_next;
        prev->m_next = next;
        next->m_prev = prev;

        delete target;
        return next == &m_sentinel ? nullptr : next;
    }

private:
    void clear()
    {
        while (first() != nullptr)
        {
            erase_first();
        }
    }

    void copy_from(const List& a)
    {
        Item* last_new = nullptr;
        for (const Item* p = a.m_sentinel.m_next;
            p != &a.m_sentinel; p = p->m_next)
        {
            last_new = insert_after(last_new, p->m_data);
        }
    }

    Item m_sentinel;
};

#endif