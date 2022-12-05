#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdexcept>

template <typename Data> class List
{
public:
    class Item
    {
    private:
        Item* nextItem;
        Item* prevItem;
        Data value;
    public:
        Item *next() { return this->nextItem; }
        Item *prev() { return this->prevItem; }
        Data data() const { return this->value; }
        Item(Data data) : value(data),prevItem(0),nextItem(0) { }
        void set_next(Item* next) {
            this->nextItem = next;
        }
        void set_prev(Item* prev) {
            this->prevItem = prev;
        }
    };

    // Creates new list
    List() : headItem(0) { }

    // copy constructor
    List(const List &a)
    {
        // implement or disable this function
        throw std::runtime_error("Not yet implemented");
    }

    // assignment operator
    List &operator=(const List &a)
    {
        // implement or disable this function
        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        Item* cur = this->headItem;
        while (cur) {
            Item* next = cur->next();
            delete cur;
            cur = next;
        }
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return this->headItem;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        Item* item = new Item(data);
        
        item->set_next(headItem);
        if (headItem) headItem->set_prev(item);

        return headItem = item;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        if (!item) return 0;
        Item* new_item = new Item(data);
        
        Item* next = item->next();
        
        new_item->set_prev(item);
        new_item->set_next(next);

        item->set_next(new_item);
        if (next) next->set_prev(new_item);
        
        return new_item;
    }

    // Deletes the specified list item.
    // Returns pointer to the item next to the deleted one.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item)
    {
        Item* prev = item->prev();
        Item* next = item->next();
        delete item;

        if (prev) {
            prev->set_next(next);
            next->set_prev(prev);
        }
        else {
            next->set_prev(NULL);
            headItem = next;
        }

        return next;
    }

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (!item) return 0;
        if (!item->next()) return 0;

        Item* next = item->next();
        Item* after_next = next->next();
        delete next;

        item->set_next(after_next);
        if (after_next) after_next->set_prev(item);
        
        return after_next;
    }

private:
    Item* headItem;
};

#endif
