#ifndef LIST_H
#define LIST_H

#include <cstddef>

// Change it to desired type
typedef int Data;

class List {
  public:
    class Item {
      public:
        Item *next() { return _next; }
        Item *prev() { return _prev; }
        Data data() const { return _data; }

      private:
        // internal data here
        Data _data;
        Item *_next;
        Item *_prev;

        Item(Data data, Item *next = nullptr, Item *prev = nullptr)
            : _data(data), _next(next), _prev(prev) {}

        void setNext(Item *next) { _next = next; }
        void setPrev(Item *prev) { _prev = prev; }
        void setData(Data data) { _data = data; }

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
    const Item *first() const;

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
    // private data should be here
    Item *_head = nullptr;
    void copy(const List &other);
};

#endif
