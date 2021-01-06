//
// Created by Alex on 25.12.2020.
//

#ifndef YURILAB_STACK_H
#define YURILAB_STACK_H

#include "array.h"

template <typename TElement>
class Stack {
private:
    unsigned int _size_of_stack;
    Array<TElement> *_array;

public:
    explicit Stack(const unsigned int maxSize) {
        _size_of_stack = 0;
        _array = new Array<TElement>(maxSize);
    }

    explicit Stack() {
        _size_of_stack = 0;
        _array = new Array<TElement>(5);
    }

    ~Stack() {
        delete _array;
    }

    void push(const TElement newElement) {
        if (_array->size() <= _size_of_stack + 1){
            Array<TElement>* _new_array = new Array<TElement>(2 * _size_of_stack);
            for (size_t i = 0; i < _array->size(); ++i){
                _new_array->set(i,_array->get(i));
            }
            std::swap(_new_array, _array);
            delete _new_array;
        }
        _array->set(_size_of_stack, newElement);
        _size_of_stack++;
    }

    void pop() {
        _size_of_stack--;
    }

    TElement top() {
        return _array->get(_size_of_stack - 1);
    }

    unsigned int size() {
        return _size_of_stack;
    }
};
#endif //YURILAB_STACK_H
