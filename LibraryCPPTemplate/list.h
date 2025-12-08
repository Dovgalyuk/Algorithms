#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item* next()
        {
            return (m_next && m_next->isSentinel) ? nullptr : m_next;
        }

        Item* prev()
        {
            return (m_prev && m_prev->isSentinel) ? nullptr : m_prev;
        }

        Data data() const { return m_data; }

    private:
        // internal data here
        Item* m_next;
        Item* m_prev;
        Data  m_data;
        bool  isSentinel = false;

        friend class List;
    };

    // Creates new list
    List()
    {
        m_head = new Item;
        m_head->isSentinel = true;
        m_head->m_next = m_head;
        m_head->m_prev = m_head;
    }

    // copy constructor
    List(const List& a)
    {
        m_head = new Item;
        m_head->isSentinel = true;
        m_head->m_next = m_head;
        m_head->m_prev = m_head;

        copy_from(a);
    }

    // assignment operator
    List& operator=(const List& a)
    {
        if (this != &a) {
            clear();
            copy_from(a);
        }
        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        clear();
        delete m_head;
    }

    // Retrieves the first item from the list
    Item* first()
    {
        Item* f = m_head->m_next;
        return (f->isSentinel) ? nullptr : f;
    }

    Item* first() const
    {
        Item* f = m_head->m_next;
        return (f->isSentinel) ? nullptr : f;
    }

    Item* last()
    {
        Item* l = m_head->m_prev;
        return (l->isSentinel) ? nullptr : l;
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
        if (item == nullptr) {
            item = m_head;
        }

        Item* newItem = new Item;
        newItem->m_data = data;

        newItem->m_next = item->m_next;
        newItem->m_prev = item;

        item->m_next->m_prev = newItem;
        item->m_next = newItem;

        return newItem;
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
        if (item == nullptr) item = m_head;

        Item* victim = item->m_next;

        if (victim->isSentinel) {
            return nullptr;
        }

        item->m_next = victim->m_next;
        victim->m_next->m_prev = item;

        Item* after = item->m_next;
        Item* result = (after->isSentinel) ? nullptr : after;

        delete victim;
        return result;
    }

private:
    // private data should be here
    Item* m_head;

    void clear()
    {
        Item* it = m_head->m_next;
        while (!it->isSentinel) {
            Item* next = it->m_next;
            delete it;
            it = next;
        }
        m_head->m_next = m_head;
        m_head->m_prev = m_head;
    }

    void copy_from(const List& a)
    {
        for (Item* it = a.first(); it; it = it->next()) {
            insert_after(last(), it->data());
        }
    }
};

#endif
