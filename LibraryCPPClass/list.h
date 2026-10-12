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
        Item *next() { return next_; }
        Item *prev() { return prev_; }
        Data data() const { return data_; }
    private:
        Item(Data data, Item *prev, Item *next)
            : data_(data), prev_(prev), next_(next) {}

        Data data_;
        Item *prev_;   // предыдущий элемент, nullptr у первого
        Item *next_;   // следующий элемент, nullptr у последнего

        // список создаёт и удаляет элементы, поэтому видит их поля
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

    // The same for a constant list
    const Item *first() const;

    // Retrieves the last item of the list
    Item *last();

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
    // удаляет все элементы, нужен деструктору и оператору присваивания
    void clear();

    // копирует элементы другого списка в текущий (пустой) список
    void copy_from(const List &a);

    Item *first_;
    Item *last_;
};

#endif
