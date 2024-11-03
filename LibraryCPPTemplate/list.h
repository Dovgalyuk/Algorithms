#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data>
class List
{
public:
    class Item
    {
    public:
        Item(Data data) : data_item(data), next_item(nullptr), prev_item(nullptr) {}
        Item *next() { return next_item; }
        Item *prev() { return prev_item; }
        Data data() const { return data_item; }
    private:
        Data data_item;
        Item *next_item;
        Item *prev_item;
        friend class List<Data>;
    };

    List();
    List(const List &a);  
    List &operator=(const List &a);
    
    ~List();
    Item *first();
    Item *insert(Data data);
    Item *insert_after(Item *item, Data data);
    Item *erase_first();
    Item *erase_next(Item *item);
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
    _size = 0;
    for (Item *current = a._head; current != nullptr; current = current->next_item)
    {
        insert(current->data_item);
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

        for (Item *current = a._head; current != nullptr; current = current->next_item)
        {
            insert(current->data_item);
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
typename List<Data>::Item *List<Data>::first()
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
        new_item->next_item = _head;
        _head->prev_item = new_item;
        _head = new_item;
    }
    _size+=1;
    return new_item;
}

template <typename Data>
typename List<Data>::Item *List<Data>::insert_after(Item *item, Data data)
{
    if (item == nullptr)
        return nullptr;

    Item *new_item = new Item(data);
    new_item->next_item = item->next_item;
    new_item->prev_item = item;

    if (item->next_item)
    {
        item->next_item->prev_item = new_item;
    }
    item->next_item = new_item;

    if (item == _tail)
    {
        _tail = new_item;
    }
    _size+=1;
    return new_item;
}

template <typename Data>
typename List<Data>::Item *List<Data>::erase_first()
{
    if (_head == nullptr)
        return nullptr;

    Item *temp = _head;
    _head = _head->next_item;

    if (_head)
    {
        _head->prev_item = nullptr;
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
    if (item == nullptr || item->next_item == nullptr)
        return nullptr;

    Item *to_delete = item->next_item;
    item->next_item = to_delete->next_item;

    if (to_delete->next_item)
    {
        to_delete->next_item->prev_item = item;
    }
    else
    {
        _tail = item;
    }

    _size--;
    delete to_delete;
    return item->next_item;
}

#endif