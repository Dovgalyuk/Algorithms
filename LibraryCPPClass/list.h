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
        Item *next() { return _next; }
        Item*& next_ref() { return _next; }
        Item *prev() { return nullptr; }
        Data data() const { return _data;}

        Item()
        {
            _data = 0;
            _next = nullptr;
        }

        Item (Data data){this->_data = data;}

        Item(Data data, Item* next){
            this->_data = data;
            this->_next = next;
        }

        void SetNext(Item* next){
            this->_next = next;
        }

    private:
        Data _data;
        Item *_next;
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

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item);
private:
    void copy_recursive(Item* current);
    Item* _first;
};

#endif
