#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

struct Queue {
    List list;
    ListItem* last;

    Queue();
    void insert(int data);
    int get() const;
    void remove();
    bool empty() const;
};

#endif
