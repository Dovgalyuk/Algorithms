#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

class Queue {
   public:
    Queue() = default;
    Queue(const Queue& a) = default;
    Queue& operator=(const Queue& a) = default;
    ~Queue() = default;

    void insert(Data data);
    Data get() const;
    void remove();
    bool empty() const;

   private:
    List list_;
};

#endif