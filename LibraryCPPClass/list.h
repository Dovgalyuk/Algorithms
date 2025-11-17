#ifndef LIST_H
#define LIST_H

// Change it to desired type
typedef int Data;

class List
{
public:
    class Item
    {
    public:
        Item *next() { return _next; }
        Data data() const { return _data; }
        
    private:
        Item* _next;
        Data _data;
        Item(Data d): _next(nullptr), _data(d) {}
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

    void clear();
    void copy(const List &a);

    // Retrieves the first item from the list
    Item *first();
    Item *last();
    const Item *last() const;

    // Inserts new list item into the beginning
    Item *insert(Data data);
    Item *insert_end(Data data);

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data);

    // Erases the specified item
    // Returns pointer to the item next to the deleted one
    // O(n) complexity for singly-linked list
    Item *erase(Item *item);

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first();

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // O(1)
    Item *erase_next(Item *item);

private:
    Item* _head = nullptr;
    Item* _tail = nullptr;
};

#endif
