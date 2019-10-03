#ifndef STACK_H
#define STACK_H
#include "list_s.hpp"
// Stack
// Stores integer values inside
template<typename Data>
class Stack {
	List<Data>* cont;
public:
	// Creates empty stack
	Stack();
	// Deletes the stack
	~Stack();
	// Pushes data on top of the stack
	// Should be O(1) on average
	void push(Data data);
	// Retrives the last element from the stack
	Data get();
	// Removes the last element from the stack
	// Should be O(1)
	void pop();
	// Returns true if the stack is empty
	bool empty();
};

template<typename Data>
Stack< Data > ::Stack()
{
	cont = new List<Data>;
	cont->insert(Data());
}

template<typename Data>
Stack< Data > ::~Stack()
{
	delete cont;
}

template<typename Data>
void Stack < Data > ::push(Data data)
{
	cont->insert_after(cont->first(), data);
}

template<typename Data>
Data Stack < Data > ::get()
{
	return cont->item_data(cont->item_next(cont->first()));
}

template<typename Data>
void Stack < Data > ::pop()
{
	cont->erase_next(cont->first());
}

template<typename Data>
bool Stack < Data > ::empty()
{
	return !(cont->item_next(cont->first()));
}
#endif