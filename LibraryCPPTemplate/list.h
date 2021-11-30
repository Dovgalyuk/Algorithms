#ifndef LIST_H
#define LIST_H
#include <functional>

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return _next; }
        Item *prev() { return _prev; }
        Data data() const { return _data; }
        explicit Item(Data data, Item* next = nullptr, Item* prev = nullptr): _data(data), _next(next), _prev(prev) {}
        void setPrev(Item* item) {_prev = item;}
        void setNext(Item* item) {_next = item;}
    private:
        // internal data here
        Item* _next;
        Item* _prev;
        Data _data;
    };

    // Creates new list
    List() : _head(nullptr), _tail(nullptr)
    {

    }

    // Destroys the list and frees the memory
    ~List()
    {
        Item* current = _head;
        while (current != _tail) {
            _head = current->prev();
            delete current;
            current = _head;
        }
        delete _head;
        size = 0;
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return _head;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        if (_head == nullptr) {
            _head = new Item(data);
            _tail = _head;
            size = 1;
            return _tail;
        } else {
            Item* newItem = new Item(data);
            newItem->setNext(_head);
            _head->setPrev(newItem);
            _head = newItem;
            _head->setPrev(_tail);
            _tail->setNext(_head);
            size++;
            return newItem;
        }
    }

    Item *insert_end(Data data)
    {
        if (_head == nullptr) {
            _head = new Item(data);
            _tail = _head;
            size = 1;
            return _tail;
        }
        else{
            Item* newItem = new Item(data);
            newItem->setPrev(_tail);
            _tail->setNext(newItem);
            _tail = newItem;
            _tail->setNext(_head);
            _head->setPrev(_tail);

            size++;
            return newItem;
        }
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        Item* newItem = new Item(data);
        newItem->setPrev(item);
        newItem->setNext(item->next());
        item->next()->setPrev(newItem);
        item->setNext(newItem);

        size++;
        return newItem;
    }

    // Deletes the specified list item.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item)
    {
        //Item* prev = item->prev();
        if (_head == item)
            _head = item->next();
        item->next()->setPrev(item->prev());
        item->prev()->setNext(item->next());



        delete item;
        size--;
        return _head;
    }

    // Deletes the list item following the specified one
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        return nullptr;
    }

    void getList()
    {
        Item *element = _head;
        for (int i = 0; i < size; ++i) {
            std::cout << element->data() << " ";
            element = element->next();
        }
    }

private:
    // private data should be here
    Item* _tail;
    Item* _head;
    int size;
};
#endif