#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#include <cstddef>

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item* next() { return _next; }
        Item* prev() { return _prev; }
        Data& data() { return _data; }
        const Data& data() const { return _data; }
    private:
        Item* _next = nullptr;
        Item* _prev = nullptr;
        Data _data{};

        Item(const Data& d) : _next(nullptr), _prev(nullptr), _data(d) {}

        friend class List<Data>;
    };

    // Creates new list
    List() : _head(nullptr)
    {
    }

    // copy constructor
    List(const List& a) : _head(nullptr)
    {
        copy(a);
    }

    // assignment operator
    List& operator=(const List& a)
    {
        if (this != &a)
        {
            clear();
            copy(a);
        }
        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        clear();
    }

    // Retrieves the first item from the list
    Item* first() const
    {
        return _head;
    }

    // Inserts new list item into the beginning
    Item* insert(const Data& data)
    {
        return insert_after(nullptr, data);
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item* insert_after(Item* item, const Data& data)
    {
        Item* new_item = new Item(data);

        if (!item)
        {
            new_item->_next = _head;
            if (_head)
            {
                _head->_prev = new_item;
            }
            _head = new_item;
        }
        else
        {
            new_item->_next = item->_next;
            new_item->_prev = item;
            if (item->_next)
            {
                item->_next->_prev = new_item;
            }
            item->_next = new_item;
        }

        return new_item;
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
        Item* to_delete = item ? item->_next : _head;
        if (!to_delete)
        {
            return nullptr;
        }

        if (to_delete == _head)
        {
            _head = to_delete->_next;
        }

        if (to_delete->_next)
        {
            to_delete->_next->_prev = to_delete->_prev;
        }
        if (to_delete->_prev)
        {
            to_delete->_prev->_next = to_delete->_next;
        }

        Item* next_item = to_delete->_next;
        delete to_delete;

        return next_item;
    }
private:
    Item* _head = nullptr;

    void copy(const List& a)
    {
        Item* last = nullptr;
        for (Item* it = a._head; it; it = it->_next)
        {
            last = insert_after(last, it->_data);
        }
    }

    void clear()
    {
        while (_head)
        {
            erase_first();
        }
    }
};

#endif
