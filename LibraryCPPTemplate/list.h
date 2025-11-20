#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#include <stdexcept>

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return m_next; }
        Item *prev() { return m_prev; }
        Data data() const { return m_data; }
    private:
        // internal data here
        Data m_data;
        Item *m_next;
        Item *m_prev;

        friend class List;
    };

    // Creates new list
    List() 
        : m_head(nullptr), m_tail(nullptr)
    { }

    // copy constructor
    List(const List &a)
        : m_head(nullptr), m_tail(nullptr)
    {
        for (Item* it = a.m_head; it != nullptr; it = it->m_next) {
            insert_after(m_tail, it->m_data);
        }
    }

    // assignment operator
    List &operator=(const List &a)
    {
        if (this == &a) {
            return *this;
        }

        while (m_head != nullptr) {
            erase_first();
        }

        for (Item *it = a.m_head; it; it = it->m_next) {
            insert_after(m_tail, it->m_data);
        }

        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        while (m_head)
        {
            Item *it = m_head;
            m_head = m_head->m_next;
            delete it;
        }
        m_tail = nullptr;
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return m_head;
    }

    const Item *first() const
    {
        return m_head;
    }

    // Retrieves the last item from the list
    Item *last()
    {
        return m_tail;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        Item *newItem = new Item;
        newItem->m_data = data;
        newItem->m_next = m_head;
        newItem->m_prev = nullptr;
        
        if (m_head != nullptr) {
            m_head->m_prev = newItem;
        } else {
            m_tail = newItem;
        }
        
        return (m_head = newItem);
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data)
    {
        if (item == nullptr) {
            return insert(data);
        } 

        Item *newItem = new Item;
        newItem->m_data = data;
        newItem->m_prev = item;
        newItem->m_next = item->m_next;
        
        if (item->m_next != nullptr) {
            item->m_next->m_prev = newItem;
        } else {
            m_tail = newItem;
        }

        return (item->m_next = newItem);
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        if (m_head != nullptr) {
            Item *next = m_head->m_next;
            delete m_head;

            m_head = next;
            
            if (m_head == nullptr) {
                m_tail = nullptr;
            } else {
                m_head->m_prev = nullptr;
            }

            return m_head;
        }

        return nullptr;
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (item == nullptr) {
            return erase_first();
        }

        Item* itemToDelete = item->m_next;
        if (itemToDelete == nullptr)
            return nullptr;

        item->m_next = itemToDelete->m_next;
        if (item->m_next != nullptr) {
            item->m_next->m_prev = item;
        } else {
            m_tail = item;
        }

        delete itemToDelete;
        return item->m_next;
    }
private:
    // private data should be here
    Item *m_head;
    Item *m_tail;
};

#endif
