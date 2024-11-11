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
        Item(Item* prev,Item * next,Data const & data):m_data(data),m_prev(prev),m_next(next){}
        Item *next() { return m_next; }
        void set_next(Item * next){
            m_next = next;
        }
        void set_prev(Item * prev){
            m_prev = prev;
        }
        void set_data(Data const & data){
            m_data = data;
        }
        Item *prev() { return m_prev; }
        Data data() const { return m_data; }
    private:
        // internal data here
        Data m_data;
        Item* m_prev;
        Item* m_next;
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
    Item const *first() const;

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
    // private data should be here
    Item * m_head;
};

#endif
