//
// Created by Alex on 14.01.2021.
//

#ifndef DOLBOYBLAB_STACK_H
#define DOLBOYBLAB_STACK_H
#include "List.h"

template <typename T>
class Stack {
private:
    unsigned int _size_of_stack;
    List<T> *_list;

public:

    explicit Stack() {
        _size_of_stack = 0;
        _list = new List<T>();
    }

    ~Stack() {
        delete _list;
    }

    void push(const T& newElement) {
        _list->insert(newElement);
        _size_of_stack++;
    }

    void pop() {
        _list->drop_first();
        _size_of_stack--;
    }

    const T& top() {
        return _list->first();
    }

    unsigned int size() {
        return _size_of_stack;
    }
};
#endif //DOLBOYBLAB_STACK_H
