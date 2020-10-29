#ifndef VECTOR_H
#define VECTOR_H

// Vector (dynamic array)
// Stores integer values inside
typedef int Data;

struct Vector
{
private:
	size_t _size;
	Data* _elem;
	size_t _space;
public:
	Vector();
	~Vector();
	Data GetValue(size_t index);
	void Set(size_t index, Data value);
	size_t GetSize();
	void Resize(size_t size);
	size_t GetCapacity();
};

//// Creates vector
//Vector *vector_create();
//
//// Deletes vector structure and internal data
//void vector_delete(Vector *vector);
//
//// Retrieves vector element with the specified index
//Data vector_get(const Vector *vector, size_t index);
//
//// Sets vector element with the specified index
//void vector_set(Vector *vector, size_t index, Data value);
//
//// Retrieves current vector size
//size_t vector_size(const Vector *vector);
//
//// Changes the vector size (may increase or decrease)
//// Should be O(1) on average
//void vector_resize(Vector *vector, size_t size);

#endif
