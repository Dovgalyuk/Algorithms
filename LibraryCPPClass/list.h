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
        Item(Data data);

        Item *prev();
        Item *next();
        Data data() const;
    private:
        Item *_prev;
        Item *_next;
        Data _data;

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

    // Retrieves the last item from the list
    Item *last();

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
    Item *_list;
    Item *_listLast;
};

#endif
