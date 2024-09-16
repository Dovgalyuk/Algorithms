#ifndef LIST_H
#define LIST_H

#include <cstddef>

typedef int Data;

class List {
public:
    class Item
    {
    public:
        // Creator for crate new Item
        Item(Item *prev, Item *next, int data) {
            _prev = prev;
            _next = next;
            _data = data;
        };

        // Setter for set value in object
        void _setNext(Item *next) { _next = next; };
        void _setPrev(Item *prev) { _prev = prev; };
        void _setData(int data) { _data = data; };
        // iterator
        Item *_iterator() { return _next; };

        Item *next() { return _next; }
        Item *prev() { return _prev; }
        Data data() const { return Data(); }
    private:
        Item *_next;
        Item *_prev;
        int _data;
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
    size_t _size;
    Item *_lastItem;
    Item *_firstItem;
};

#endif
