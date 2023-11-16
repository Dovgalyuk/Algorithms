#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#include <cstddef> // for size_t

template <typename Data>
class List
{
public:
    class Item
    {
    public:
        Data _data;
        Item* _next;
        Item* _prev;

        Item(Data data, Item* prev = nullptr, Item* next = nullptr) : _data(data), _prev(prev), _next(next) {}

        Item* next() { return _next; }
        Item* prev() { return _prev; }
        Data data() const { return _data; }
    };

private:
    Item* _head;
    Item* _tail;
    size_t _size;

public:
    
    List() : _head(nullptr), _tail(nullptr), _size(0) {}
    ~List()
    {
        while (_head)
        {
            Item* temp = _head;
            _head = _head->next();
            delete temp;
        }
    }

    Item* first() { return _head; }

    Item* insert(Data data)
    {
        Item* newItem = new Item(data, nullptr, _head);
        if (_head)
        {
            _head->_prev = newItem;
        }
        _head = newItem;
        if (_tail == nullptr)
        {
            _tail = newItem;
        }
        _size++;
        return newItem;
    }

    Item* insert_after(Item* item, Data data)
    {
        if (!item)
        {
            return insert(data);
        }
        Item* newItem = new Item(data, item, item->_next);
        if (item->_next)
        {
            item->_next->_prev = newItem;
        }
        item->_next = newItem;
        if (item == _tail)
        {
            _tail = newItem;
        }
        _size++;
        return newItem;
    }

    Item* erase_first()
    {
        if (!_head) return nullptr;
        Item* nextItem = _head->_next;
        delete _head;
        _head = nextItem;
        if (_head)
        {
            _head->_prev = nullptr;
        }
        else
        {
            _tail = nullptr;
        }
        _size--;
        return nextItem;
    }

    Item* erase_next(Item* item)
    {
        if (!item || !item->_next) return nullptr;
        Item* nextItem = item->_next->_next;
        delete item->_next;
        item->_next = nextItem;
        if (nextItem)
        {
            nextItem->_prev = item;
        }
        else
        {
            _tail = item;
        }
        _size--;
        return nextItem;
    }

    size_t size() const { return _size; }
};

#endif // LIST_TEMPLATE_H
