#ifndef STACK_H
#define STACK_H

#include <cstddef>

// Change it to desired type
typedef int Data;

class Stack
{
public:
    
    Stack();

    //копирование конструктора
    Stack(const Stack &a);

    // оператор присваивания
    Stack &operator=(const Stack &a);

    //удаление стека
    ~Stack();

    // пуш элемента в стек
    // Should be O(1) on average
    void push(Data data);

    //последнего элемента из стека
    Data get() const;

    // Removes the last element from the stack
    // Should be O(1)
    void pop();

    // Returns true if the stack is empty
    bool empty() const;

private:
    // private data should be here
};

#endif
