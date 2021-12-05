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
    List() : firstItem(nullptr), lastItem(nullptr)
    {

    }

    // Destroys the list and frees the memory
    ~List()
    {
        Item* current = firstItem;
        while (current != lastItem) {
            firstItem = current->next();
            delete current;
            current = firstItem;
        }
        delete firstItem;
        size = 0;
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return firstItem;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        if (firstItem == nullptr) {
            firstItem = new Item(data);
            lastItem = firstItem;
            size = 1;
            return lastItem;
        } else {
            Item* newItem = new Item(data);
            newItem->setNext(firstItem);
            firstItem->setPrev(newItem);
            firstItem = newItem;
            firstItem->setPrev(lastItem);
            lastItem->setNext(firstItem);
            size++;
            return newItem;
        }
    }

    Item *insert_end(Data data)
    {
        if (firstItem == nullptr) {
            firstItem = new Item(data);
            lastItem = firstItem;
            size = 1;
            return lastItem;
        }
        else{
            Item* newItem = new Item(data);
            newItem->setPrev(lastItem);
            lastItem->setNext(newItem);
            lastItem = newItem;
            lastItem->setNext(firstItem);
            firstItem->setPrev(lastItem);

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
        if (firstItem == item)
            firstItem = item->next();
        item->next()->setPrev(item->prev());
        item->prev()->setNext(item->next());



        delete item;
        size--;
        return firstItem;
    }

    // Deletes the list item following the specified one
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        return nullptr;
    }

    void getList()
    {
        Item *elem = firstItem;
        for (int i = 0; i < size; i++) {
            std::cout << elem->data() << " ";
            elem = elem->next();
        }
    }

    int Size(){
        return size;
    }

private:
    // private data should be here
    Item* firstItem;
    Item* lastItem;
    int size;
};
#endif