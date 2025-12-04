#ifndef LIST_H
#define LIST_H

#include <cstddef>

// Type of data stored in the list
typedef int Data;

class List
{
public:
    class Item
    {
    public:
        // Creates a list item containing 'data' and pointers to previous and next items
        Item(Data data = Data(), Item* prev = nullptr, Item* next = nullptr)
            : adata(data), previtem(prev), nextitem(next) {}

        // Returns pointer to the next item
        Item* next() { return nextitem; }

        // Returns pointer to the previous item
        Item* prev() { return previtem; }

        // Returns stored data
        Data data() const { return adata; }

        // Sets pointer to the next item
        void setNext(Item* next) { nextitem = next; }

        // Sets pointer to the previous item
        void setPrev(Item* prev) { previtem = prev; }

    private:
        // Stored value
        Data adata;

        // Pointers to previous and next items (doubly-linked list)
        Item* previtem;
        Item* nextitem;
    };

    // Creates an empty list
    List();

    // Copy constructor
    List(const List& a);

    // Assignment operator
    List& operator=(const List& a);

    // Destroys the list and frees memory
    ~List();

    // Returns pointer to the first item in the list
    Item* first();
    const Item* first() const;

    // Inserts a new item at the beginning of the list
    Item* insert(Data data);

    // Inserts a new item after the specified one.
    // If 'item' is null, inserts at the beginning.
    Item* insert_after(Item* item, Data data);

    // Removes the first item.
    // Returns the item that follows the removed one.
    Item* erase_first();

    // Removes the item after the specified one.
    // If 'item' is null, removes the first item.
    // Returns the item that follows the removed one.
    Item* erase_next(Item* item);

private:
    // Pointer to the first item in the list
    Item* aitem;

    // Copies items from another list
    void copyitems(const List& a);

    // Removes all items from the list
    void clearlist();
};

#endif
