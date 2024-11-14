#ifndef LIST_H
#define LIST_H

#include <cstddef>

typedef int Data;

class List
{
public:
    class Item
    {
    public:
        Item(Data value, Item* next = nullptr) : lData(value), lNext(next) {};

        Item *next() const { return lNext; }
        Item *prev() { return nullptr; }
        Data data() const { return lData; }

        void set_next(Item* next) { lNext = next; }
    private:
        // internal data here
        Data lData;
        Item* lNext;
    };

    // Creates new list
    List();

    // copy constructor
    List(const List &a);

    // assignment operator
    List &operator=(const List &a);

    // Destroys the list and frees the memory
    ~List();

    // Retrieves the first item from the list
    Item *first() const;

    // Inserts new list item into the beginning
    Item *insert(Data data);

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data);

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first();

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item);
private:
    Item* lHead;
    // private data should be here
};

#endif
