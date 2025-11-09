#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include "vector.h"

template <std::copyable Data, class Container = Vector<Data>> 
class Stack
{
public:
    Stack() = default;

    explicit Stack(std::size_t size) {
        container_.reserve(size);
    }

    Stack(const Stack &a) : container_(a.container_)
    {}

    Stack(Stack&& a) : container_(std::move(a.container_)) 
    {}

    Stack &operator=(const Stack &a)
    {
        if (&a != this) {
            container_ = a.container_;
        }
        return *this;
    }

    Stack& operator=(Stack&& a) {
        if(&a != this) {
            container_ = std::move(a.container_);
        }
        return *this;
    }

    friend void swap(Stack& a, Stack& b) {
        std::swap(a.container_, b.container_);
    }

    // Deletes the stack
    ~Stack()
    {
    }

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(const Data& data)
    {
        container_.push_back(data);
    }

    void push(Data&& data) {
        container_.push_back(data);
    }

    template<class... Args>
    void emplace(Args&&... args) {
        container_.emplace_back(std::forward<Args>(args)...);
    }

    Data& top() {
        if (empty()) {
            throw std::underflow_error("top on empty stack");
        }
        return container_.back();
    }

    const Data& top() const {
        if (empty()) {
            throw std::underflow_error("top on empty stack");
        }
        return container_.back();
    }

    // alias for stack test
    // Retrieves the last element from the stack
    Data get() const
    {
        return top();
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        if (empty()) {
            throw std::underflow_error("pop on empty stack");
        }

        container_.pop_back();
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return container_.empty();
    }

    std::size_t size() const {
        return container_.size();
    }

    const Container container() const {
        return container_;
    }

private:
    Container container_;
};

#endif
