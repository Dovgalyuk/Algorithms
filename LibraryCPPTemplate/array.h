
#ifndef
#define 

#include "stack.h"

template <typename TElement>
class StackByList {
private:
    unsigned int _size_of_stack;
    SinglyLinkedList<TElement> *_list;

public:

    explicit StackByList() {
        _size_of_stack = 0;
        _list = new SinglyLinkedList<TElement>();
    }

    ~StackByList() {
        delete _list;
    }

    void push(const TElement& newElement) {
        _list->add(newElement);
        _size_of_stack++;
    }

    void pop() {
        _list->drop_first();
        _size_of_stack--;
    }

    const TElement& top() {
        return _list->first();
    }

    unsigned int size() {
        return _size_of_stack;
    }
};
#endif 
