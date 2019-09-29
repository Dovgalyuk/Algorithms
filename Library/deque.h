#ifndef DEQUE_H
#define DEQUE_H

// Deque
// Stores integer values inside
#include "defines.h"

struct Chunk
{
	Data* elements;
};

struct Deque {
	Chunk* chunks;
	size_t first_index;
	size_t last_index;
};


// Creates empty deque
Deque* deque_create();

// Deletes the deque
void deque_delete(Deque* deque);

// Retrieves deque element with the specified index
Data deque_get(const Deque* deque, size_t index);

// Sets deque element with the specified index
void deque_set(Deque* deque, size_t index, Data value);

// Retrieves current deque size
size_t deque_size(const Deque* deque);

// Pushes data on top of the deque
// Should be O(1) on average
void deque_push_back(Deque* deque, Data data);

// Retrives the last element from the deque
Data deque_last(const Deque* deque);

// Removes the last element from the deque
// Should be O(1) on average
void deque_pop_back(Deque* deque);

// Inserts an element to the beginning of deque
// Should be O(1) on average
void deque_push_front(Deque* deque, Data data);

// Retrives first element from the deque
Data deque_first(const Deque* deque);

// Removes first element from the deque
// Should be O(1) on average
void deque_pop_front(Deque* deque);

// Returns true if the deque is empty
bool deque_empty(const Deque* deque);

#endif
