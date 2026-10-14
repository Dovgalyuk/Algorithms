#ifndef STACK_H
#define STACK_H

#include "list.h"
#include <stdexcept>
#include <cstddef>

template <typename Data>
class Stack
{
private:
    List<Data> list;

public:
    bool empty() const
    {
        return list.empty();
    }

    std::size_t size() const
    {
        return list.size();
    }

    // Верх стека
    void push(const Data& value)
    {
        list.pushFront(value);
    }

    Data& top()
    {
        return list.front();
    }

    const Data& top() const
    {
        return list.front();
    }

    void pop()
    {
        list.popFront();
    }

    // AnnoyingScript также работает
    // с нижней частью стека

    void pushBottom(const Data& value)
    {
        list.pushBack(value);
    }

    Data& bottom()
    {
        return list.back();
    }

    const Data& bottom() const
    {
        return list.back();
    }

    void popBottom()
    {
        list.popBack();
    }

    void reverse()
    {
        list.reverse();
    }

    void clear()
    {
        list.clear();
    }

    Data& at(std::size_t index)
    {
        return list.at(index);
    }

    const Data& at(std::size_t index) const
    {
        return list.at(index);
    }
};

#endif