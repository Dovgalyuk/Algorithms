#ifndef QUEUE_H
#define QUEUE_H
#include "stack.hpp"

template<typename Data>
class Queue
{
	Stack<Data> *in;
	Stack<Data> *out;
	void shift_o();
public:
	// Create empty queue
	Queue();
	// Deletes queue
	~Queue();
	// Includes new element into the queue
	// Should be O(1)
	void insert(Data data);
	// Retrieves first element from the queue
	Data get();
	// Removes first element from the queue
	// Should be O(1)
	void remove();
	// Returns true if the queue is empty
	bool empty();
};

template<typename Data>
Queue<Data>::Queue()
{
	in = new Stack<Data>;
	out = new Stack<Data>;
}

template<typename Data>
Queue<Data>::~Queue()
{
	delete in;
	delete out;
}

template<typename Data>
void Queue<Data>::shift_o()
{
	if (!out->empty())
		return;
	while (!in->empty())
	{
		out->push(in->get());
		in->pop();
	}
}

template<typename Data>
void Queue<Data>::insert(Data data)
{
	in->push(data);
}

template<typename Data>
Data Queue<Data>::get()
{
	shift_o();
	return out->get();
}

template<typename Data>
void Queue<Data>::remove()
{
	shift_o();
	out->pop();
}

template<typename Data>
bool Queue<Data>::empty()
{
	return (out->empty()&&in->empty());
}
#endif