#ifndef LIST_H
#define LIST_H

typedef int Data;

class List {
public:
    struct Item {
        Data data;
        Item* next;
        Item* prev;
    };

    List();
    List(const List& other);
    List& operator=(const List& other);
    ~List();

    Item* first() const;
    Item* insert(Data data);
    Item* erase(Item* item);
    bool empty() const;

private:
    Item* dummy;
};

#endif
