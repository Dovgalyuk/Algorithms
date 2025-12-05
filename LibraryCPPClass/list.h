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

    private:
        Data adata;
        Item* previtem;
        Item* nextitem;

        // Only List is allowed to modify internal links
        void setNext(Item* next) { nextitem = next; }
        void setPrev(Item* prev) { previtem = prev; }

        friend class List;
    };

    List();
    List(const List& a);
    List& operator=(const List& a);
    ~List();

    Item* first();
    const Item* first() const;

    Item* insert(Data data);
    Item* insert_after(Item* item, Data data);

    Item* erase_first();
    Item* erase_next(Item* item);

private:
    Item* aitem;

    void copyitems(const List& a);
    void clearlist();
};

#endif
