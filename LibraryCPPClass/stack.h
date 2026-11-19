#ifndef STACK_H
#define STACK_H

#include <cstddef>

#include "vector.h"

class Stack {
   public:
    Stack() = default;
    Stack(const Stack& a) = default;
    Stack& operator=(const Stack& a) = default;
    ~Stack() = default;

    void push(const Data& data);
    const Data& get() const;
    void pop();
    bool empty() const;

   private:
    Vector v_;
};

#endif
