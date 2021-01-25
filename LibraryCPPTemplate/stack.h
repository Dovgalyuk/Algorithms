#pragma once
#include "array.h"

// Stack
// Stores integer values inside
typedef int Data;

template <typename T>
struct MyStack
{
public:
	MyStack()
	{
		_array = new Array<T>(10);
	}
	~MyStack()
	{
		delete _array;
	}
	void Push(T value)
	{
		if (_topIndex + 1 == _array->size())
		{
			_array->set(_topIndex, value);
			Array<T>* new_array = new Array<T>(_array->size() * 2);
			new_array->copy_values(_array);
			delete _array;
			_array = new_array;
		}
		_topIndex++;
	}
	T Get()
	{
		return _array->get(_topIndex - 1);
	}
	void Pop()
	{
		_topIndex--;
	}
	bool Empty()
	{
		return (_topIndex == 0);
	}
private:
	Array<T>* _array;
	int _topIndex = 0;
};

// Creates empty stack
//Stack *stack_create();
//
//// Deletes the stack
//void stack_delete(Stack *stack);
//
//// Pushes data on top of the stack
//// Should be O(1) on average
//void stack_push(Stack *stack, Data data);
//
//// Retrives the last element from the stack
//Data stack_get(const Stack *stack);
//
//// Removes the last element from the stack
//// Should be O(1)
//void stack_pop(Stack *stack);
//
//// Returns true if the stack is empty
//bool stack_empty(const Stack *stack);

