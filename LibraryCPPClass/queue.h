#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

typedef int Data;

class Queue {
public:
    Queue();
    Queue(const Queue& a);
    Queue& operator=(const Queue& a);
    ~Queue();
    void insert(Data data);
    Data get() const;
    void remove();
    bool empty() const;
private:
    List list;
};

#endif
