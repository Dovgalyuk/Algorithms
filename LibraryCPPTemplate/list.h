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
    List()
    {
        elem->setNext(elem);
        elem->setPrev(elem);
        firstItem = elem;
        lastItem = elem;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        Item* current = firstItem;
        while (current != elem) {
            firstItem = current->next();
            delete current;
            current = firstItem;
        }
        delete elem;
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return firstItem;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        return insert_after(elem, data);
    }

    Item *insert_end(Data data)
    {
        Item* newItem = new Item(data);
        newItem->setNext(elem);
        newItem->setPrev(elem->prev());
        elem->prev()->setNext(newItem);
        elem->setPrev(newItem);
        if(firstItem == elem && lastItem == elem)
        {
            firstItem = newItem;
            lastItem = newItem;
        }
        else if(newItem->next() == elem && newItem->prev() == lastItem)
        {
            lastItem = newItem;
        }
        return newItem;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        Item* newItem = new Item(data);
        newItem->setNext(item->next());
        item->next()->setPrev(newItem);
        newItem->setPrev(item);
        item->setNext(newItem);
        if (firstItem == elem && lastItem == elem) {
            firstItem = newItem;
            lastItem = newItem;
        }
        else if (newItem->next() == firstItem && newItem->prev() == elem)
        {
            firstItem = newItem;
        }

        return newItem;
    }

    // Deletes the specified list item.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item)
    {
        //Item* prev = item->prev();
        if (item == firstItem && item == lastItem) {
            firstItem = elem;
            lastItem = elem;
        }
        else
        {
            if (firstItem == item)
            {
                firstItem = item->next();
            }
        }
        item->next()->setPrev(item->prev());
        item->prev()->setNext(item->next());

        delete item;
        return firstItem;
    }

    // Deletes the list item following the specified one
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        return nullptr;
    }

    void showList() {
        Item *num = firstItem;
        while (num != elem) {
            std::cout << num->data() << ' ';
            num = num->next();
        }
    }

    bool empty()
    {
        if (firstItem == elem && lastItem == elem) {
            return true;
        }
        else
            return false;
    }

private:
    // private data should be here
    Item* firstItem;
    Item* lastItem;
    Item* elem = new Item(0);
};
#endif