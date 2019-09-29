#include "deque.h"

const size_t CHUNK_SIZE = 128;

void deuqe_add_chunk(Deque* deque, bool atStart) {
	size_t chunksAmont = (deque->last_index - 1) / CHUNK_SIZE + 1;
	Chunk* newChunks = new Chunk[chunksAmont + 1];
	Chunk* newChunk = new Chunk();
	newChunk->elements = new Data[CHUNK_SIZE];
	if (atStart) {
		for (size_t i = 0; i < chunksAmont; i++) {
			newChunks[i + 1] = deque->chunks[i];
		}
		newChunks[0] = *newChunk;
		deque->first_index += CHUNK_SIZE;
		deque->last_index += CHUNK_SIZE;
	}
	else {
		for (size_t i = 0; i < chunksAmont; i++) {
			newChunks[i] = deque->chunks[i];
		}
		newChunks[chunksAmont] = *newChunk;
	}
	delete[] deque->chunks;
	deque->chunks = newChunks;
}

void deuqe_remove_chunk(Deque* deque, bool atStart) {
	size_t chunksAmont = (deque->last_index - 1) / CHUNK_SIZE + 1;
	Chunk* newChunks = new Chunk[chunksAmont - 1];
	if (atStart) {
		for (size_t i = 0; i < chunksAmont - 1; i++) {
			newChunks[i] = deque->chunks[i + 1];
		}
		deque->first_index -= CHUNK_SIZE;
		deque->last_index -= CHUNK_SIZE;
	}
	else {
		for (size_t i = 0; i < chunksAmont - 1; i++) {
			newChunks[i] = deque->chunks[i];
		}
	}
	delete[] deque->chunks;
	deque->chunks = newChunks;
}

Deque* deque_create()
{
	Deque* newDeque = new Deque();
	Chunk* newChunk = new Chunk();
	newChunk->elements = new Data[CHUNK_SIZE];
	newDeque->chunks = { newChunk };
	newDeque->first_index = newDeque->last_index = CHUNK_SIZE / 2;
	return newDeque;
}

void deque_delete(Deque* deque)
{
	size_t chunksAmont = (deque->last_index - 1) / CHUNK_SIZE + 1;
	for (size_t i = 0; i < chunksAmont; i++) {
		delete[] deque->chunks[i].elements;
	}
	delete[] deque->chunks;
	delete deque;
}

Data deque_get(const Deque* deque, size_t index)
{
	size_t realIndex = deque->first_index + index;
	size_t chunkIndex = realIndex / CHUNK_SIZE;
	return deque->chunks[chunkIndex].elements[realIndex - CHUNK_SIZE * chunkIndex];
}

void deque_set(Deque* deque, size_t index, Data value)
{
	size_t realIndex = deque->first_index + index;
	if (realIndex + 1 > deque->last_index) {
		deque->last_index = realIndex + 1;
	}
	size_t chunkIndex = realIndex / CHUNK_SIZE;
	deque->chunks[chunkIndex].elements[realIndex - CHUNK_SIZE * chunkIndex] = value;
}

inline size_t deque_size(const Deque* deque)
{
	return deque->last_index - deque->first_index;
}


void deque_push_back(Deque* deque, Data data)
{
	size_t chunksAmont = (deque->last_index - 1) / CHUNK_SIZE + 1;
	if (deque->last_index == chunksAmont * CHUNK_SIZE)
	{
		deuqe_add_chunk(deque, false);
	}
	deque_set(deque, deque_size(deque), data);
}

Data deque_last(const Deque* deque)
{
	return deque_get(deque, deque_size(deque) - 1);
}

void deque_pop_back(Deque* deque)
{
	size_t chunksAmont = (deque->last_index - 1) / CHUNK_SIZE + 1;
	if (deque->last_index - 1 == (chunksAmont - 1) * CHUNK_SIZE)
	{
		deuqe_remove_chunk(deque, false);
	}
	deque->last_index--;
}

void deque_push_front(Deque* deque, Data data)
{
	if (deque->first_index == 0) {
		deuqe_add_chunk(deque, true);
	}
	deque->first_index--;
	
	deque->chunks[0].elements[deque->first_index] = data;
}


Data deque_first(const Deque* deque)
{
	return deque_get(deque, 0);
}

void deque_pop_front(Deque* deque)
{
	if (deque->first_index == CHUNK_SIZE - 1)
	{
		deuqe_remove_chunk(deque, true);
	}

	deque->first_index++;
}


bool deque_empty(const Deque* deque)
{
	return deque_size(deque) == 0;
}

