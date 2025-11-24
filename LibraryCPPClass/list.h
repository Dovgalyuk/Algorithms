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
        Item *next() { return m_next; }
        Item *prev() { return m_prev; }
        Data data() const { return m_data; }
    private:
        // internal data here
        Item *m_next = nullptr;
        Item *m_prev = nullptr;
        Data m_data;
        Item(Data d) : m_data(d) {}
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
    Item* first() const;
    Item* last() const;

    bool empty() const;

    // Inserts new list item into the beginning
    Item *insert(Data data);

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data);

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first();

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item);
    void erase(Item* item);

private:
    // private data should be here
    Item *m_first = nullptr;
    Item *m_last = nullptr;

    void clear();
    void copy_from(const List& a);
};

#endif
