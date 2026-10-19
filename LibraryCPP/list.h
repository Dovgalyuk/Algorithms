#ifndef LIST_H
#define LIST_H

struct ListItem {
    int data;
    ListItem* next;
};

struct List {
    ListItem* dummy;

    List();
    ~List();
    ListItem* first() const;
    ListItem* insert_after(ListItem* item, int data);
    void erase_after(ListItem* item);
};

#endif
