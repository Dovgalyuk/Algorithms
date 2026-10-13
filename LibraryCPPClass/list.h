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
        Item *next();
        Item *next() const;
        Item *prev();
        Item *prev() const;
        Data data() const;

    private:
        explicit Item(Data value);
        Data value;
        Item *next_item;
        Item *prev_item;
        friend class List;
    };

    List();
    List(const List &a);
    List &operator=(const List &a);
    ~List();

    Item *first();
    Item *first() const;
    Item *last();
    Item *last() const;
    Item *insert(Data data);
    Item *insert_after(Item *item, Data data);
    Item *erase_first();
    Item *erase_next(Item *item);

private:
    Item *first_item;
    Item *last_item;
};

#endif
