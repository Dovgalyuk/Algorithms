#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

class Queue {
public:
    Queue();
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);
    ~Queue();

    void insert(Data data);
    Data get() const;
    void remove();
    bool empty() const;

private:
    List list;
};

#endif
