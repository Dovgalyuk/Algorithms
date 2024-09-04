#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data>
class List
{
public:
    class Item
    {
    public:
        Item(Data data) : _data(data), _next(nullptr), _prev(nullptr) {}

        Item *next() { return _next; }
        Item *prev() { return _prev; }
        Data data() { return _data; }

    private:
        Data _data;
        Item *_next;
        Item *_prev;

        friend class List<Data>;
    };

    List();
    
    List(const List &a);
    
    List &operator=(const List &a);
    
    ~List();
    
    Item *first() const;
    
    Item *insert(Data data);
    
    Item *insert_after(Item *item, Data data);
    
    Item *erase_first();
    
    Item *erase_next(Item *item);

    Item *insert_back(Data data);

private:
    Item *_head;
    Item *_tail;
    size_t _size;
};

template <typename Data>
List<Data>::List() : _head(nullptr), _tail(nullptr), _size(0) {}

template <typename Data>
List<Data>::List(const List &a)
{
    _head = _tail = nullptr;
    _size = a._size;
    for (Item *current = a._tail; current != nullptr; current = current->_prev)
    {
        insert(current->_data);
    }
}

template <typename Data>
List<Data> &List<Data>::operator=(const List &a)
{
    if (this != &a)
    {
        while (_head)
        {
            erase_first();
        }

        for (Item *current = a._head; current != nullptr; current = current->_next)
        {
            insert(current->_data);
        }
    }
    return *this;
}

template <typename Data>
List<Data>::~List()
{
    while (_head)
    {
        erase_first();
    }
}

template <typename Data>
typename List<Data>::Item *List<Data>::first() const
{
    return _head;
}

template <typename Data>
typename List<Data>::Item *List<Data>::insert(Data data)
{
    Item *new_item = new Item(data);
    if (_head == nullptr)
    {
        _head = _tail = new_item;
    }
    else
    {
        new_item->_next = _head;
        _head->_prev = new_item;
        _head = new_item;
    }
    _size++;
    return new_item;
}

template <typename Data>
typename List<Data>::Item *List<Data>::insert_back(Data data)
{
    Item *new_item = new Item(data);
    if (_tail == nullptr)
    {
        _head = _tail = new_item;
    }
    else
    {
        _tail->_next = new_item;
        new_item->_prev = _tail;
        _tail = new_item;
    }
    _size++;
    return new_item;
}

template <typename Data>
typename List<Data>::Item *List<Data>::insert_after(Item *item, Data data)
{
    if (item == nullptr)
        return nullptr;

    Item *new_item = new Item(data);
    new_item->_next = item->_next;
    new_item->_prev = item;

    if (item->_next)
    {
        item->_next->_prev = new_item;
    }
    item->_next = new_item;

    if (item == _tail)
    {
        _tail = new_item;
    }

    _size++;
    return new_item;
}

template <typename Data>
typename List<Data>::Item *List<Data>::erase_first()
{
    if (_head == nullptr)
        return nullptr;

    Item *temp = _head;
    _head = _head->_next;

    if (_head)
    {
        _head->_prev = nullptr;
    }
    else
    {
        _tail = nullptr;
    }

    _size--;
    delete temp;
    return _head;
}

template <typename Data>
typename List<Data>::Item *List<Data>::erase_next(Item *item)
{
    if (item == nullptr || item->_next == nullptr)
        return nullptr;

    Item *to_delete = item->_next;
    item->_next = to_delete->_next;

    if (to_delete->_next)
    {
        to_delete->_next->_prev = item;
    }
    else
    {
        _tail = item;
    }

    _size--;
    delete to_delete;
    return item->_next;
}

#endif