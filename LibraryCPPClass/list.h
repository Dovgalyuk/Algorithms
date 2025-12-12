#ifndef LIST_H
#define LIST_H

#include <cstddef>

// Change it to desired type
typedef int Data;

class List
{
public:
    class Item
    {
    public:
        Item(Data data, Item* next = nullptr, Item* prev = nullptr): data_(data), prev_(prev), next_(next) {}

        Item *next() { return next_; }
        Item *prev() { return prev_; }
        Data data() const { return data_; }

        void setNextPtr(Item *next);
        void setPrevPtr(Item *prev);

    private:
        // internal data here
        Data data_;
        Item *prev_;
        Item *next_;
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
    Item *first();

    // Inserts new list item into the beginning
    Item *insert(Data data);

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data);

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first();

    // Returns true if the list is empty
    bool list_empty() const;

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item);

    // Returns the element from the end
    Item *get_end_item() const;

    Data data_head() const;

private:
    // private data should be here
    Item* head_; 
    Item* tail_;
};

#endif
