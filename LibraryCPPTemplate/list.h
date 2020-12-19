#ifndef LIST_H
#define LIST_H

struct Coord
{
    int row, col, dist;
};

// MyList
// Stores integer values inside
typedef int Data;

struct ListItem
{
private:
    ListItem* _next;
    Coord _value;
    friend class MyList;
public:
    ListItem(Coord, ListItem*);
    Coord list_item_data() const;
    ListItem* list_item_next() const;
};

struct MyList
{
private:
    friend class Stack;
    friend class Queue;
    ListItem* head;
    size_t _length;
public:
    MyList();
    ~MyList();

    size_t get_length() const;
    ListItem* list_first() const;
    void list_insert_after(ListItem*, Coord);
    void push_front(Coord);
    void pop();
    void list_erase_next(ListItem*);
};







// Creates new list
//MyList *list_create();

// Destroys the list and frees the memory
//void list_delete(MyList *list);

// Retrieves the first item from the list
//ListItem *list_first(MyList *list);

// Extracts data from the list item
//Data list_item_data(const ListItem *item);

// Returns list item following after the specified one
//ListItem *list_item_next(ListItem *item);

// Returns previous element for the specified item.
// Not applicable for the singly linked lists.
//ListItem *list_item_prev(ListItem *item);

// Inserts new list item into the beginning
//ListItem *list_insert(MyList *list, Data data);

// Inserts new list item after the specified item
//ListItem *list_insert_after(MyList *list, ListItem *item, Data data);

// Deletes the specified list item.
// Not applicable for the singly linked lists.
// Should be O(1)
//ListItem *list_erase(MyList *list, ListItem *item);

// Deletes the list item following the specified one
// Should be O(1)
ListItem *list_erase_next(MyList *list, ListItem *item);

#endif
