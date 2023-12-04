#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data>
class List
{
public:
    class Item
    {
    public:
        Data _data;
        Item* _prev;
        Item* _next;

        Item(Data data, Item* prev = nullptr, Item* next = nullptr) : _data(data), _prev(prev), _next(next) {}

        Item* prev() { return _prev; }
        Item* next() { return _next; }
        Data data() const { return _data; }
        Data& get_data() { return _data; }
    };

private:
    Item* _head;
    Item* _tail;

public:

    List() : _head(nullptr), _tail(nullptr) {}
    ~List()
    {
        while (_head)
        {
            Item* temp = _head->next();
            delete _head;
            _head = temp;
        }
        _tail = nullptr;
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
        return newItem;
    }

    List(const List& other) : _head(nullptr), _tail(nullptr) { copy(other); }

    List& operator=(const List& other)
    {
        if (this != &other)
        {
            clear();
            copy(other);
        }
        return *this;
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
        return nextItem;
    }
private:
    void copy(const List& other)
    {
        for (Item* item = other._head; item; item = item->next())
        {
            insert(item->data());
        }
    }

    void clear()
    {
        while (_head)
        {
            Item* temp = _head->next();
            delete _head;
            _head = temp;
        }
        _tail = nullptr;
    }
};

#endif // LIST_TEMPLATE_H