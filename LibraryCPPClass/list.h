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
        Item *next() const { return _next; }
        Item *prev() const { return _prev; }
        Data data() const { return _data; }
        void next(Item *item) { _next = item; }
        void prev(Item *item) { _prev = item; }
        void data(Data d) { _data = d; }
    private:
        Data _data;
        Item *_next;
        Item *_prev;
        // internal data here
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
    Item *head;
    Item *tail;
    // private data should be here
};

#endif
