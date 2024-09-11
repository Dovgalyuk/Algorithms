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
        // Constructor to initialize the item with data
        Item(Data data);
        Item *next();
        Item *prev();
        Data data() const;
    private:
        // internal data here
        Data data_;       // Holds the data of the item
        Item *next_;      // Pointer to the next item
        Item *prev_;      // Pointer to the previous item

        // The List class is a friend for accessing private data
        friend class List;
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
    Item *insert_after(Item *item, Data data);

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first();

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item);
private:
    Item *head_;  // Pointer to the first item in the list
    Item *tail_;  // Pointer to the last item in the list
};

#endif
