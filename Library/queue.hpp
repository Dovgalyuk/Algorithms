#ifndef QUEUE_H
#define QUEUE_H
#include "stack.hpp"

template<typename Data>
class Queue
{
	Stack<Data> *in;
	Stack<Data> *out;
	void shift_o() const;
public:
	// Create empty queue
	Queue();
	// Deletes queue
	~Queue();
	// Includes new element into the queue
	// Should be O(1)
	void insert(const Data &data);
	// Retrieves first element from the queue
	Data get() const;
	// Removes first element from the queue
	// Should be O(1)
	void remove();
	// Returns true if the queue is empty
	bool empty() const;
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
void Queue<Data>::shift_o() const
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
void Queue<Data>::insert(const Data &data)
{
	in->push(data);
}

template<typename Data>
Data Queue<Data>::get() const
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
bool Queue<Data>::empty() const
{
	return (out->empty()&&in->empty());
}
#endif