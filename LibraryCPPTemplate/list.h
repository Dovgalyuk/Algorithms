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
    List() : firstItem(nullptr)
    {
    }

    // Destroys the list and frees the memory
    ~List()
    {
        Item *item;
        while (item)
        {
            item = first();
            if (firstItem->next() == firstItem && firstItem->prev() == firstItem)
            {
                firstItem = nullptr;
                delete item;
                break;
            }
            firstItem = item->next();
            firstItem->setPrev(item->prev());
            item->prev()->setNext(firstItem);
            delete item;
        }
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return firstItem;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        Item* newItem = new Item(data);
        if (firstItem == nullptr)
        {
            firstItem = newItem;
            firstItem->setNext(firstItem);
            firstItem->setPrev(firstItem);
        }
        else {
            newItem->setNext(firstItem);
            newItem->setPrev(firstItem->prev());
            firstItem->prev()->setNext(newItem);
            firstItem->setPrev(newItem);
            firstItem = newItem;
        }

        return firstItem;
    }

    Item *insert_end(Data data)
    {
        Item *newItem = new Item(data);
        if (firstItem == nullptr)
        {
            firstItem = newItem;
            firstItem->setNext(firstItem);
            firstItem->setPrev(firstItem);
        }
        else {

            newItem->setNext(firstItem);
            newItem->setPrev(firstItem->prev());
            firstItem->prev()->setNext(newItem);
            firstItem->setPrev(newItem);
        }
        return newItem;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        Item* newItem = new Item(data);
        newItem->setNext(item->next());
        newItem->setPrev(item);
        item->next()->setPrev(newItem);
        item->setNext(newItem);

        return newItem;
    }

    // Deletes the specified list item.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item)
    {
        if (firstItem->next() == firstItem && firstItem->prev() == firstItem) {
            firstItem = nullptr;
            delete item;
            return firstItem;
        }
        else {
            if (item == firstItem)
                firstItem = item->next();
            item->next()->setPrev(item->prev());
            item->prev()->setNext(item->next());
            Item *buff_item = item->next();
            delete item;
            return buff_item;
        }


    }

    // Deletes the list item following the specified one
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        return nullptr;
    }

    void get_list(){
        Item *item = first();
        do {
            std::cout << item->data() << ' ';
            item = item->next();
        }while (item != firstItem);
    }

    bool empty()
    {
        if (firstItem == nullptr)
            return true;
        else
            return false;
    }

private:
    // private data should be here

    Item* firstItem;
};
#endif